/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Broadcom Corporation
 * Copyright 2013 Linaro Limited
 */

#ifndef _CLOCK_BCM21654_H
#define _CLOCK_BCM21654_H

/*
 * This file defines the values used to specify clocks provided by
 * the clock control units (CCUs) on Broadcom BCM21654 SoC.
 */

/* bcm21654 CCU device tree "compatible" strings */
#define BCM21654_DT_ROOT_CCU_COMPAT	"brcm,bcm21654-root-ccu"
#define BCM21654_DT_AON_CCU_COMPAT	"brcm,bcm21654-aon-ccu"
#define BCM21654_DT_MASTER_CCU_COMPAT	"brcm,bcm21654-master-ccu"
#define BCM21654_DT_SLAVE_CCU_COMPAT	"brcm,bcm21654-slave-ccu"

/* root CCU clock ids */

#define BCM21654_ROOT_CCU_FRAC_1M		0

/* aon CCU clock ids */

#define BCM21654_AON_CCU_HUB_TIMER		0
#define BCM21654_AON_CCU_HUB_TIMER_APB		1
#define BCM21654_AON_CCU_PMU_BSC		2
#define BCM21654_AON_CCU_PMU_BSC_APB		3

/* master CCU clock ids */

#define BCM21654_MASTER_CCU_SDIO1		0
#define BCM21654_MASTER_CCU_SDIO2		1
#define BCM21654_MASTER_CCU_SDIO3		2
#define BCM21654_MASTER_CCU_SDIO1_SLEEP		3
#define BCM21654_MASTER_CCU_SDIO2_SLEEP		4
#define BCM21654_MASTER_CCU_SDIO3_SLEEP		5
#define BCM21654_MASTER_CCU_SDIO1_AHB		6
#define BCM21654_MASTER_CCU_SDIO2_AHB		7
#define BCM21654_MASTER_CCU_SDIO3_AHB		8
#define BCM21654_MASTER_CCU_USB_OTG_AHB		9

/* slave CCU clock ids */

#define BCM21654_SLAVE_CCU_UARTB		0
#define BCM21654_SLAVE_CCU_UARTB2		1
#define BCM21654_SLAVE_CCU_UARTB3		2
#define BCM21654_SLAVE_CCU_BSC1			3
#define BCM21654_SLAVE_CCU_BSC2			4
#define BCM21654_SLAVE_CCU_UARTB_APB		5
#define BCM21654_SLAVE_CCU_UARTB2_APB		6
#define BCM21654_SLAVE_CCU_UARTB3_APB		7
#define BCM21654_SLAVE_CCU_BSC1_APB		8
#define BCM21654_SLAVE_CCU_BSC2_APB		9

#endif /* _CLOCK_BCM21654_H */
