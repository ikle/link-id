/*
 * IGB methods
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>

#include "ethtool.h"

static int link_calc_sum (struct link *o, int iv, unsigned offset, int count)
{
	unsigned s, i, w;

	for (s = iv, i = offset; count > 0; ++i, --count) {
		if (!link_read_word (o, i, &w))
			return -1;

		s += w;
	}

	return s;
}

#define IGB_EEPROM_CHECKSUM	0x3f
#define IGB_EEPROM_SUM		0xbaba

static int igb_calc_checksum (struct link *o, unsigned *sum)
{
	int s;

	if ((s = link_calc_sum (o, 0, 0, IGB_EEPROM_CHECKSUM)) < 0)
		return 0;

	*sum = (IGB_EEPROM_SUM - s) & 0xffff;
	return 1;
}

static int igb_validate_checksum (struct link *o)
{
	unsigned sum, real;

	if (!link_read_word (o, IGB_EEPROM_CHECKSUM, &sum) ||
	    !igb_calc_checksum (o, &real))
		return 0;

	if (sum != real) {
		errno = EBADMSG;
		return 0;
	}

	return 1;
}

static int igb_update_checksum (struct link *o)
{
	unsigned sum;

	return	igb_calc_checksum (o, &sum) &&
		link_write_word (o, IGB_EEPROM_CHECKSUM, sum);
}

static int igb_read_id (struct link *o, unsigned *vendor, unsigned *device)
{
	unsigned c;	/* Initialization Control Word 1 */

	if (!igb_validate_checksum (o)	||
	    !link_read_word (o, 0x0a, &c))
		return 0;

	if ((c & 0x02) == 0) {		/* Load Subsystem IDs = false */
		*vendor = 0x8086;
		*device = 0x0000;
		return 1;
	}

	return	link_read_word (o, 0x0b, device) &&
		link_read_word (o, 0x0c, vendor);
}

static int igb_write_id (struct link *o, unsigned vendor, unsigned device)
{
	unsigned c;	/* Initialization Control Word 1 */

	return	igb_validate_checksum (o)           &&
		link_read_word (o, 0x0a, &c)        &&
		link_write_word (o, 0x0a, c | 0x02) &&
		link_write_word (o, 0x0b, device)   &&
		link_write_word (o, 0x0c, vendor)   &&
		igb_update_checksum (o);
}

struct link_ops igb_ops = {
	.validate_checksum	= igb_validate_checksum,
	.update_checksum	= igb_update_checksum,
	.read_id		= igb_read_id,
	.write_id		= igb_write_id,
};
