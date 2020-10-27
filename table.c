/*
 * Magic to ops mapping
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ethtool.h"

/* Device-specific operations table */

extern struct link_ops igb_ops;

struct table table[] = {
	/* e1000e */

	{ 0x10d38086, &igb_ops		},	/* 82574L		*/
	{ 0x15028086, &igb_ops		},	/* 82579LM		*/

	/* igb */

	{ 0x04388086, &igb_ops		},	/* DH89xxCC, sgmii	*/
	{ 0x043a8086, &igb_ops		},	/* DH89xxCC, serdes	*/
	{ 0x043c8086, &igb_ops		},	/* DH89xxCC, backplane	*/
	{ 0x04408086, &igb_ops		},	/* DH89xxCC, sfp	*/

	{ 0x10a78086, &igb_ops		},	/* 82575EB, copper	*/
	{ 0x10a98086, &igb_ops		},	/* 82575EB, fiber	*/
	{ 0x10c98086, &igb_ops		},	/* 82576, copper	*/
	{ 0x10d68086, &igb_ops		},	/* 82575GB, quad copper	*/
	{ 0x10e68086, &igb_ops		},	/* 82576, fiber		*/
	{ 0x10e78086, &igb_ops		},	/* 82576, serdes	*/
	{ 0x10e88086, &igb_ops		},	/* 82576, quad copper	*/

	{ 0x150a8086, &igb_ops		},	/* 82576NS, copper	*/
	{ 0x150d8086, &igb_ops		},	/* 82576, quad serdes	*/
	{ 0x150e8086, &igb_ops		},	/* 82580, copper	*/
	{ 0x150f8086, &igb_ops		},	/* 82580, fiber		*/
	{ 0x15108086, &igb_ops		},	/* 82580, serdes	*/
	{ 0x15118086, &igb_ops		},	/* 82580, sgmii		*/
	{ 0x15168086, &igb_ops		},	/* 82580, dual copper	*/
	{ 0x15188086, &igb_ops		},	/* 82576NS, serdes	*/
	{ 0x15218086, &igb_ops		},	/* I350, copper		*/
	{ 0x15228086, &igb_ops		},	/* I350, fiber		*/
	{ 0x15238086, &igb_ops		},	/* I350, serdes		*/
	{ 0x15248086, &igb_ops		},	/* I350, sgmii		*/
	{ 0x15268086, &igb_ops		},	/* 82576, quad copper ET2 */
	{ 0x15278086, &igb_ops		},	/* 82580, quad fiber	*/

	{ 0x15338086, &igb_ops		},	/* I210, copper		*/
	{ 0x15368086, &igb_ops		},	/* I210, fiber		*/
	{ 0x15378086, &igb_ops		},	/* I210, serdes		*/
	{ 0x15388086, &igb_ops		},	/* I210, sgmii		*/
	{ 0x15398086, &igb_ops		},	/* I211, copper		*/

	{ 0x157b8086, &igb_ops		},	/* I210, copper	flashless */
	{ 0x157c8086, &igb_ops		},	/* I210, serdes flashless */

	{ 0x1f408086, &igb_ops		},	/* I354, backplane 1.0	*/
	{ 0x1f418086, &igb_ops		},	/* I354, sgmii		*/
	{ 0x1f458086, &igb_ops		},	/* I354, backplane 2.5	*/

	/* terminator */

	{				}
};
