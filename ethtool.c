/*
 * Ethtool helpers
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <unistd.h>

#include <linux/netlink.h>
#include <linux/sockios.h>

#include "ethtool.h"

static int link_control (struct link *o, void *cmd)
{
	o->ifr.ifr_data = cmd;
	return ioctl (o->fd, SIOCETHTOOL, &o->ifr) != -1;
}

static int link_get_drvinfo (struct link *o)
{
	o->info.cmd = ETHTOOL_GDRVINFO;
	return link_control (o, &o->info);
}

extern struct link_ops null_ops;

int link_open (struct link *o, const char *name)
{
	struct table *p;

	memset (&o->ifr, 0, sizeof (o->ifr));
	strncpy (o->ifr.ifr_name, name, sizeof (o->ifr.ifr_name));

	if ((o->fd = socket (AF_INET, SOCK_DGRAM, 0)) == -1 &&
	    (o->fd = socket (AF_NETLINK, SOCK_RAW, NETLINK_GENERIC)) == -1)
		return 0;

	if (!link_get_drvinfo (o))
		goto no_info;

	o->ops = &null_ops;

	if (link_write_enable (o))
		for (p = table; p->magic != 0; ++p)
			if (o->magic == p->magic) {
				o->ops = p->ops;
				break;
			}

	o->magic = 0;
	return 1;
no_info:
	close (o->fd);
	return 0;
}

void link_close (struct link *o)
{
	close (o->fd);
}

int link_read_word (struct link *o, unsigned offset, unsigned *w)
{
	struct {
		struct ethtool_eeprom head;
		unsigned char data[2];
	} c;

	c.head.cmd = ETHTOOL_GEEPROM;
	c.head.magic = 0;
	c.head.offset = offset * 2;
	c.head.len = 2;

	if (!link_control (o, &c.head))
		return 0;

	*w = c.head.data[0] | ((unsigned) c.head.data[1] << 8);
	return 1;
}

int link_write_enable (struct link *o)
{
	struct {
		struct ethtool_eeprom head;
		unsigned char data[2];
	} c;

	if (o->info.eedump_len == 0)
		return 0;

	c.head.cmd = ETHTOOL_GEEPROM;
	c.head.magic = 0;
	c.head.offset = 0;
	c.head.len = 2;

	if (!link_control (o, &c.head))
		return 0;

	o->magic = c.head.magic;
	return 1;
}

int link_write_word (struct link *o, unsigned offset, unsigned w)
{
	struct {
		struct ethtool_eeprom head;
		unsigned char data[2];
	} c;

	c.head.cmd = ETHTOOL_SEEPROM;
	c.head.magic = o->magic;
	c.head.offset = offset * 2;
	c.head.len = 2;
	c.head.data[0] = (w >> 0) & 0xff;
	c.head.data[1] = (w >> 8) & 0xff;

	return link_control (o, &c.head);
}
