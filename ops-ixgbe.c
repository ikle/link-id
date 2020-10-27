/*
 * IXGBE methods
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

#define IXGBE_EEPROM_CHECKSUM	0x3f
#define IXGBE_EEPROM_SUM	0xbaba
#define IXGBE_PCIE_ANALOG_PTR	0x03
#define IXGBE_FW_PTR		0x0f

static int ixgbe_calc_checksum (struct link *o, unsigned *sum)
{
	int s;
	unsigned i, p, len;

	if ((s = link_calc_sum (o, 0, 0, IXGBE_EEPROM_CHECKSUM)) < 0)
		return 0;

	for (i = IXGBE_PCIE_ANALOG_PTR; i < IXGBE_FW_PTR; ++i) {
		if (!link_read_word (o, i, &p))
			return 0;

		if (p == 0 || p == 0xffff)
			continue;

		if (!link_read_word (o, p, &len))
			return 0;

		if ((s = link_calc_sum (o, s, p + 1, len)) < 0)
			return 0;
	}

	*sum = (IXGBE_EEPROM_SUM - s) & 0xffff;
	return 1;
}

static int ixgbe_validate_checksum (struct link *o)
{
	unsigned sum, real;

	if (!link_read_word (o, IXGBE_EEPROM_CHECKSUM, &sum) ||
	    !ixgbe_calc_checksum (o, &real))
		return 0;

	if (sum != real) {
		errno = EBADMSG;
		return 0;
	}

	return 1;
}

static int ixgbe_update_checksum (struct link *o)
{
	unsigned sum;

	return	ixgbe_calc_checksum (o, &sum) &&
		link_write_word (o, IXGBE_EEPROM_CHECKSUM, sum);
}

static int ixgbe_read_id (struct link *o, unsigned *vendor, unsigned *device)
{
	unsigned p;	/* PCIe General Configuration Module */
	unsigned c;	/* PCIe Control 3 */

	if (!ixgbe_validate_checksum (o)	||
	    !link_read_word (o, 0x06, &p)	||
	    !link_read_word (o, p + 0x07, &c))
		return 0;

	if ((c & 0x02) == 0) {		/* Load Subsystem IDs = false */
		*vendor = 0x8086;
		*device = 0x0000;
		return 1;
	}

	return	link_read_word (o, p + 0x08, device) &&
		link_read_word (o, p + 0x09, vendor);
}

static int ixgbe_write_id (struct link *o, unsigned vendor, unsigned device)
{
	unsigned p;	/* PCIe General Configuration Module */
	unsigned c;	/* PCIe Control 3 */

	return	ixgbe_validate_checksum (o)		&&
		link_read_word (o, 0x06, &p)		&&
		link_read_word (o, p + 0x07, &c)	&&
		link_write_word (o, p + 0x07, c | 0x02)	&&
		link_write_word (o, p + 0x08, device)	&&
		link_write_word (o, p + 0x09, vendor)	&&
		ixgbe_update_checksum (o);
}

struct link_ops ixgbe_ops = {
	.validate_checksum	= ixgbe_validate_checksum,
	.update_checksum	= ixgbe_update_checksum,
	.read_id		= ixgbe_read_id,
	.write_id		= ixgbe_write_id,
};
