/*
 * Default methods
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>

#include "ethtool.h"

static int null_validate_checksum (struct link *o)
{
	errno = ENOTSUP;
	return 0;
}

static int null_update_checksum (struct link *o)
{
	errno = ENOTSUP;
	return 0;
}

static int null_read_id (struct link *o, unsigned *vendor, unsigned *device)
{
	errno = ENOTSUP;
	return 0;
}

static int null_write_id (struct link *o, unsigned vendor, unsigned device)
{
	errno = ENOTSUP;
	return 0;
}

struct link_ops null_ops = {
	.validate_checksum	= null_validate_checksum,
	.update_checksum	= null_update_checksum,
	.read_id		= null_read_id,
	.write_id		= null_write_id,
};
