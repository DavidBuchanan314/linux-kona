/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Core definitions for Dialog DA2083 PMIC
 *
 * Copyright (C) 2012 Dialog Semiconductor Ltd.
 * Copyright (C) 2025 (Mainline port)
 */

#ifndef __LINUX_MFD_DA2083_CORE_H
#define __LINUX_MFD_DA2083_CORE_H

#include <linux/device.h>
#include <linux/regmap.h>

/* DA2083 Regulators */
enum da2083_regulator_id {
	DA2083_ID_BUCK1,
	DA2083_ID_BUCK2,
	DA2083_ID_BUCK3,
	DA2083_ID_BUCK4,

	DA2083_ID_LDO1,
	DA2083_ID_LDO2,
	DA2083_ID_LDO3,
	DA2083_ID_LDO4,
	DA2083_ID_LDO5,
	DA2083_ID_LDO6,
	DA2083_ID_LDO7,
	DA2083_ID_LDO8,
	DA2083_ID_LDO9,
	DA2083_ID_LDO10,
	DA2083_ID_LDO11,
	DA2083_ID_LDO12,
	DA2083_ID_LDO13,
	DA2083_ID_LDO14,
	DA2083_ID_LDO15,
	DA2083_ID_LDO16,
	DA2083_ID_LDO17,
	DA2083_ID_LDO_AUD,

	DA2083_NUM_REGULATORS,
};

/* DA2083 IRQs */
enum da2083_irq {
	DA2083_IRQ_EVF = 0,
	DA2083_IRQ_ETBAT2,
	DA2083_IRQ_EVDD_LOW,
	DA2083_IRQ_EVDD_MON,
	DA2083_IRQ_EALARM,
	DA2083_IRQ_ESEQRDY,
	DA2083_IRQ_ETICK,

	DA2083_IRQ_ENONKEY_LO,
	DA2083_IRQ_ENONKEY_HI,
	DA2083_IRQ_ENONKEY_HOLDON,
	DA2083_IRQ_ENONKEY_HOLDOFF,
	DA2083_IRQ_ETBAT1,
	DA2083_IRQ_EADCEOM,

	DA2083_IRQ_ETA,
	DA2083_IRQ_ENJIGON,

	DA2083_IRQ_EGPI0,

	DA2083_NUM_IRQ
};

/**
 * struct da2083 - DA2083 PMIC device
 * @dev: Parent device
 * @regmap: Register map
 * @irq: Primary IRQ
 * @chip_id: Chip ID read from device
 */
struct da2083 {
	struct device *dev;
	struct regmap *regmap;
	int irq;
	u8 chip_id;
};

/* Core functions */
extern const struct regmap_config da2083_regmap_config;
int da2083_device_init(struct da2083 *da2083);
void da2083_device_exit(struct da2083 *da2083);

#endif /* __LINUX_MFD_DA2083_CORE_H */
