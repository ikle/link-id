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
extern struct link_ops ixgbe_ops;

struct table table[] = {
	/* e1000e */

	{ 0x105e8086, &igb_ops		},	/* 82571EB, copper	*/
	{ 0x105f8086, &igb_ops		},	/* 82571EB, fiber	*/
	{ 0x10608086, &igb_ops		},	/* 82571EB, serdes	*/
	{ 0x10a48086, &igb_ops		},	/* 82571EB, quad copper	*/
	{ 0x10a58086, &igb_ops		},	/* 82571EB, quad fiber	*/
	{ 0x10b98086, &igb_ops		},	/* 82572EI		*/
	{ 0x10bc8086, &igb_ops		},	/* 82571EB, quad copper LP */
	{ 0x10d58086, &igb_ops		},	/* 82571PT, quad copper	*/
	{ 0x10d98086, &igb_ops		},	/* 82571EB, dual serdes	*/
	{ 0x10da8086, &igb_ops		},	/* 82571EB, quad serdes	*/
	{ 0x107d8086, &igb_ops		},	/* 82572EI, copper	*/
	{ 0x107e8086, &igb_ops		},	/* 82572EI, fiber	*/
	{ 0x107f8086, &igb_ops		},	/* 82572EI, serdes	*/
	{ 0x108b8086, &igb_ops		},	/* 82573E		*/
	{ 0x108c8086, &igb_ops		},	/* 82573E IAMT		*/
	{ 0x109a8086, &igb_ops		},	/* 82573L		*/
	{ 0x10d38086, &igb_ops		},	/* 82574L		*/
	{ 0x10f68086, &igb_ops		},	/* 82574LA		*/
	{ 0x15028086, &igb_ops		},	/* 82579LM		*/
	{ 0x150c8086, &igb_ops		},	/* 82583V		*/

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

	/* ixgbe */

	{ 0x10b68086, &ixgbe_ops	},	/* 82598		*/

	{ 0x10c68086, &ixgbe_ops	},	/* 82598 AF, dual port	*/
	{ 0x10c78086, &ixgbe_ops	},	/* 82598 AF		*/
	{ 0x10c88086, &ixgbe_ops	},	/* 82598 AT		*/

	{ 0x10db8086, &ixgbe_ops	},	/* 82598EB SFP LOM	*/
	{ 0x10dd8086, &ixgbe_ops	},	/* 82598EB CX4		*/

	{ 0x10e18086, &ixgbe_ops	},	/* 82598 SR, dual port	*/
	{ 0x10ec8086, &ixgbe_ops	},	/* 82598 CX4, dual port	*/

	{ 0x10f18086, &ixgbe_ops	},	/* 82598 DA, dual port	*/
	{ 0x10f48086, &ixgbe_ops	},	/* 82598EB XF LR	*/
	{ 0x10f78086, &ixgbe_ops	},	/* 82599 KX4		*/
	{ 0x10f88086, &ixgbe_ops	},	/* 82599 combo backplane */
	{ 0x10f98086, &ixgbe_ops	},	/* 82599 CX4		*/
	{ 0x10fb8086, &ixgbe_ops	},	/* 82599ES SFP		*/
	{ 0x10fc8086, &ixgbe_ops	},	/* 82599 XAUI LOM	*/

	{ 0x15078086, &ixgbe_ops	},	/* 82599 SFP EM		*/
	{ 0x15088086, &ixgbe_ops	},	/* 82598 BX		*/
	{ 0x150b8086, &ixgbe_ops	},	/* 82598 AT2		*/
	{ 0x15148086, &ixgbe_ops	},	/* 82599 KX4 MEZZ	*/
	{ 0x15178086, &ixgbe_ops	},	/* 82599 KR		*/
	{ 0x151c8086, &ixgbe_ops	},	/* 82599 T3 LOM		*/

	{ 0x15298086, &ixgbe_ops	},	/* 82599 SFP FCoE	*/
	{ 0x152a8086, &ixgbe_ops	},	/* 82599 backplane FCoE	*/

	{ 0x154a8086, &ixgbe_ops	},	/* 82599 SFP SF QP	*/
	{ 0x154d8086, &ixgbe_ops	},	/* 82599 SFP SF2	*/
	{ 0x154f8086, &ixgbe_ops	},	/* 82599 LS		*/

	{ 0x15578086, &ixgbe_ops	},	/* 82599EN SFP		*/
	{ 0x15588086, &ixgbe_ops	},	/* 82599 QSFP SF QP	*/

	/* terminator */

	{				}
};
