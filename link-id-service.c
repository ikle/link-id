/*
 * Ethernet Interface ID tool
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include "ethtool.h"

static int usage (void)
{
	fprintf (stderr, "usage:\n\tlink-id <iface> [<vendor>:<device>]\n");

	return 1;
}

static int write_id (struct link *o, const char *id)
{
	unsigned vendor, device;

	if (sscanf (id, "%x:%x", &vendor, &device) != 2 ||
	    vendor > 0x10000 || device > 0x10000) {
		fprintf (stderr, "E: wrong identifier format\n");
		return 0;
	}

	if (!link_write_enable (o) ||
	    !link_write_id (o, vendor, device)) {
		perror ("link-id: cannot write identifier");
		return 0;
	}

	return 1;
}

int main (int argc, char *argv[])
{
	struct link o;
	unsigned vendor, device;
	int status = 1;

	if (argc < 2 || argc > 3)
		return usage ();

	if (!link_open (&o, argv[1])) {
		perror ("link-id: cannot open link");
		return 1;
	}

	printf ("name\t= %.16s\nslot\t= %.32s\ndriver\t= %.32s\n",
		o.ifr.ifr_name, o.info.bus_info, o.info.driver);

	if (argc > 2)
		status = write_id (&o, argv[2]);

	if (link_read_id (&o, &vendor, &device))
		printf ("id\t= %04x:%04x\n", vendor, device);

	link_close (&o);
	return status ? 0 : 1;
}
