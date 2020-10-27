/*
 * Ethtool helpers
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef ETHTOOL_H
#define ETHTOOL_H  1

#include <netinet/in.h>

#include <linux/ethtool.h>
#include <linux/if.h>

struct link {
	struct ifreq ifr;
	int fd;
	struct ethtool_drvinfo info;
	__u32 magic;

	struct link_ops *ops;
};

/* Core methods */

int  link_open  (struct link *o, const char *name);
void link_close (struct link *o);

int link_read_word (struct link *o, unsigned offset, unsigned *w);

int link_write_enable (struct link *o);
int link_write_word (struct link *o, unsigned offset, unsigned w);

/* Device-specific operations */

struct link_ops {
	int (*validate_checksum) (struct link *o);
	int (*update_checksum) (struct link *o);
	int (*read_id) (struct link *o, unsigned *vendor, unsigned *device);
	int (*write_id) (struct link *o, unsigned vendor, unsigned device);
};

static inline int link_validate_checksum (struct link *o)
{
	return o->ops->validate_checksum (o);
}

static inline int link_update_checksum (struct link *o)
{
	return o->ops->update_checksum (o);
}

static inline
int link_read_id (struct link *o, unsigned *vendor, unsigned *device)
{
	return o->ops->read_id (o, vendor, device);
}

static inline
int link_write_id (struct link *o, unsigned vendor, unsigned device)
{
	return o->ops->write_id (o, vendor, device);
}

/* magic to device ops mapping */

struct table {
	__u32 magic;
	struct link_ops *ops;
};

extern struct table table[];

#endif  /* ETHTOOL_H */
