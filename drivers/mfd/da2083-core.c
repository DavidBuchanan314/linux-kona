// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Device access for Dialog DA2083 PMIC
 *
 * Copyright (C) 2012 Dialog Semiconductor Ltd.
 * Copyright (C) 2025 (Mainline port)
 */

#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/mfd/core.h>
#include <linux/module.h>
#include <linux/regmap.h>

#include <linux/mfd/da2083/core.h>
#include <linux/mfd/da2083/registers.h>

static const struct regmap_range da2083_readable_ranges[] = {
	regmap_reg_range(DA2083_PAGECON0_REG, DA2083_CONFIGID_REG),
};

static const struct regmap_access_table da2083_readable_table = {
	.yes_ranges = da2083_readable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da2083_readable_ranges),
};

static const struct regmap_range da2083_writeable_ranges[] = {
	regmap_reg_range(DA2083_PAGECON0_REG, DA2083_ALARMY_REG),
};

static const struct regmap_access_table da2083_writeable_table = {
	.yes_ranges = da2083_writeable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da2083_writeable_ranges),
};

static const struct regmap_range da2083_volatile_ranges[] = {
	regmap_reg_range(DA2083_STATUSA_REG, DA2083_EVENTD_REG),
	regmap_reg_range(DA2083_FAULTLOG_REG, DA2083_FAULTLOG_REG),
	regmap_reg_range(DA2083_COUNTS_REG, DA2083_COUNTY_REG),
};

static const struct regmap_access_table da2083_volatile_table = {
	.yes_ranges = da2083_volatile_ranges,
	.n_yes_ranges = ARRAY_SIZE(da2083_volatile_ranges),
};

const struct regmap_config da2083_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,

	.max_register = DA2083_MAX_REGISTER,
	.rd_table = &da2083_readable_table,
	.wr_table = &da2083_writeable_table,
	.volatile_table = &da2083_volatile_table,

	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL_GPL(da2083_regmap_config);

static const struct mfd_cell da2083_devs[] = {
	{
		.name = "da2083-regulator",
		.of_compatible = "dlg,da2083-regulator",
	},
	{
		.name = "da2083-onkey",
		.of_compatible = "dlg,da2083-onkey",
	},
	{
		.name = "da2083-rtc",
		.of_compatible = "dlg,da2083-rtc",
	},
};

int da2083_device_init(struct da2083 *da2083)
{
	unsigned int chip_id;
	int ret;

	/* Read chip ID */
	ret = regmap_read(da2083->regmap, DA2083_CHIPID_REG, &chip_id);
	if (ret) {
		dev_err(da2083->dev, "Failed to read chip ID: %d\n", ret);
		return ret;
	}

	da2083->chip_id = chip_id;
	dev_info(da2083->dev, "DA2083 PMIC detected (chip ID: 0x%02x)\n",
		 chip_id);

	/* Mask all interrupts initially */
	ret = regmap_write(da2083->regmap, DA2083_IRQMASKA_REG, 0xFF);
	if (ret)
		return ret;

	ret = regmap_write(da2083->regmap, DA2083_IRQMASKB_REG, 0xFF);
	if (ret)
		return ret;

	ret = regmap_write(da2083->regmap, DA2083_IRQMASKC_REG, 0xFF);
	if (ret)
		return ret;

	ret = regmap_write(da2083->regmap, DA2083_IRQMASKD_REG, 0xFF);
	if (ret)
		return ret;

	/* Register child devices */
	ret = devm_mfd_add_devices(da2083->dev, PLATFORM_DEVID_AUTO,
				   da2083_devs, ARRAY_SIZE(da2083_devs),
				   NULL, 0, NULL);
	if (ret) {
		dev_err(da2083->dev, "Failed to add child devices: %d\n", ret);
		return ret;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(da2083_device_init);

void da2083_device_exit(struct da2083 *da2083)
{
	/* Nothing to do here for now */
}
EXPORT_SYMBOL_GPL(da2083_device_exit);

MODULE_DESCRIPTION("Core support for Dialog DA2083 PMIC");
MODULE_AUTHOR("Dialog Semiconductor");
MODULE_LICENSE("GPL");
