/*
 * Copyright (c) 2023, MediaTek Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PLAT_ETH_DEF_H_
#define _PLAT_ETH_DEF_H_

#include <stdbool.h>
#include <lib/utils_def.h>
#include <lib/mmio.h>
#include <reg_base.h>

/* SoC-specific definitions */
#define SGMII_BASE			SGMII_SBUS0_BASE
#define ETHSYS_BASE			NETSYS1_BASE
#define FE_BASE				(ETHSYS_BASE + 0x100000)

#define PDMA_BASE			PDMA_V2_BASE
#define ANA_RG3_OFFS			0x128
#define GDMA_COUNT			2

#define SWITCH_RESET_GPIO

#define TXD_SIZE			32
#define RXD_SIZE			32

#define SOC_CAPS			(MTK_GMAC2_U3_QPHY | MTK_NETSYS_V2)

#if defined(IMAGE_BL31)
#define DMA_BUF_ADDR			INTER_SRAM
#define DMA_BUF_REMAP
#elif defined(IMAGE_BL2)
#include <bl2_plat_setup.h>
#define DMA_BUF_ADDR			SCRATCH_BUF_OFFSET
#endif

/* Using built-in switch */
#define GMAC_ID				0
#define GMAC_FORCE_MODE			1
#define GMAC_FORCE_SPEED		2500
#define GMAC_FORCE_FULL_DUPLEX		1
#define GMAC_INTERFACE_MODE		PHY_INTERFACE_MODE_2500BASEX
#define SWITCH_MT7531

static inline void mtk_plat_switch_reset(bool assert)
{
#define MT7981_GPIO_BASE		0x11D00000

	mmio_write_32(MT7981_GPIO_BASE + 0x348, 0xf0000000);	/* GPIO_MODE4_CLR */
	mmio_write_32(MT7981_GPIO_BASE + 0x014, BIT(7));	/* GPIO_DIR1_SET */

	if (assert)
		mmio_write_32(MT7981_GPIO_BASE + 0x118, BIT(7));	/* GPIO_DOUT1_CLR */
	else
		mmio_write_32(MT7981_GPIO_BASE + 0x114, BIT(7));	/* GPIO_DOUT1_SET */
}

#endif /* _PLAT_ETH_DEF_H_ */
