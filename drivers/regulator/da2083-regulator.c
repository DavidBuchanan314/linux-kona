// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Regulator driver for Dialog DA2083 PMIC
 *
 * Copyright (C) 2012 Dialog Semiconductor Ltd.
 * Copyright (C) 2025 (Mainline port)
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>

#include <linux/mfd/da2083/core.h>
#include <linux/mfd/da2083/registers.h>

struct da2083_regulator_info {
	struct regulator_desc desc;
	int reg;
	int mctl_reg;
};

/* BUCK voltage table: 500mV - 2075mV in 25mV steps */
static const struct linear_range da2083_buck_ranges[] = {
	REGULATOR_LINEAR_RANGE(500000, 0, 0x3F, 25000),
};

/* LDO voltage table: 1200mV - 3330mV */
static const unsigned int da2083_ldo_voltages[] = {
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000, 2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000, 3000000, 3050000, 3100000, 3150000,
	3200000, 3250000, 3330000,
};

static const struct regulator_ops da2083_buck_ops = {
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
};

static const struct regulator_ops da2083_ldo_ops = {
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
};

#define DA2083_BUCK(_id, _name, vreg, ereg) \
	[DA2083_ID_##_id] = { \
		.desc = { \
			.name = _name, \
			.of_match = of_match_ptr(_name), \
			.regulators_node = of_match_ptr("regulators"), \
			.id = DA2083_ID_##_id, \
			.ops = &da2083_buck_ops, \
			.type = REGULATOR_VOLTAGE, \
			.n_voltages = 64, \
			.linear_ranges = da2083_buck_ranges, \
			.n_linear_ranges = ARRAY_SIZE(da2083_buck_ranges), \
			.vsel_reg = vreg, \
			.vsel_mask = DA2083_VBUCK_MASK, \
			.enable_reg = ereg, \
			.enable_mask = DA2083_REGULATOR_EN, \
			.owner = THIS_MODULE, \
		}, \
		.reg = vreg, \
	}

#define DA2083_LDO(_id, num, vreg) \
	[DA2083_ID_##_id] = { \
		.desc = { \
			.name = "ldo" #num, \
			.of_match = of_match_ptr("ldo" #num), \
			.regulators_node = of_match_ptr("regulators"), \
			.id = DA2083_ID_##_id, \
			.ops = &da2083_ldo_ops, \
			.type = REGULATOR_VOLTAGE, \
			.n_voltages = ARRAY_SIZE(da2083_ldo_voltages), \
			.volt_table = da2083_ldo_voltages, \
			.vsel_reg = vreg, \
			.vsel_mask = DA2083_VLDO_MASK, \
			.enable_reg = vreg, \
			.enable_mask = DA2083_REGULATOR_EN, \
			.owner = THIS_MODULE, \
		}, \
		.reg = vreg, \
	}

static struct da2083_regulator_info da2083_regulators[] = {
	DA2083_BUCK(BUCK1, "buck1", DA2083_BUCK1_REG, DA2083_BUCKA_REG),
	DA2083_BUCK(BUCK2, "buck2", DA2083_BUCK2_REG, DA2083_BUCKA_REG),
	DA2083_BUCK(BUCK3, "buck3", DA2083_BUCK3_REG, DA2083_BUCKB_REG),
	DA2083_BUCK(BUCK4, "buck4", DA2083_BUCK4_REG, DA2083_BUCKB_REG),

	DA2083_LDO(LDO1, 1, DA2083_LDO1_REG),
	DA2083_LDO(LDO2, 2, DA2083_LDO2_REG),
	DA2083_LDO(LDO3, 3, DA2083_LDO3_REG),
	DA2083_LDO(LDO4, 4, DA2083_LDO4_REG),
	DA2083_LDO(LDO5, 5, DA2083_LDO5_REG),
	DA2083_LDO(LDO6, 6, DA2083_LDO6_REG),
	DA2083_LDO(LDO7, 7, DA2083_LDO7_REG),
	DA2083_LDO(LDO8, 8, DA2083_LDO8_REG),
	DA2083_LDO(LDO9, 9, DA2083_LDO9_REG),
	DA2083_LDO(LDO10, 10, DA2083_LDO10_REG),
	DA2083_LDO(LDO11, 11, DA2083_LDO11_REG),
	DA2083_LDO(LDO12, 12, DA2083_LDO12_REG),
	DA2083_LDO(LDO13, 13, DA2083_LDO13_REG),
	DA2083_LDO(LDO14, 14, DA2083_LDO14_REG),
	DA2083_LDO(LDO15, 15, DA2083_LDO15_REG),
	DA2083_LDO(LDO16, 16, DA2083_LDO16_REG),
	DA2083_LDO(LDO17, 17, DA2083_LDO17_REG),
	DA2083_LDO(LDO_AUD, aud, DA2083_LDO_AUD_REG),
};

static int da2083_regulator_probe(struct platform_device *pdev)
{
	struct da2083 *da2083 = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int i;

	config.dev = da2083->dev;
	config.regmap = da2083->regmap;

	for (i = 0; i < ARRAY_SIZE(da2083_regulators); i++) {
		rdev = devm_regulator_register(&pdev->dev,
					       &da2083_regulators[i].desc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev,
				"Failed to register %s regulator\n",
				da2083_regulators[i].desc.name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}

static struct platform_driver da2083_regulator_driver = {
	.driver = {
		.name = "da2083-regulator",
	},
	.probe = da2083_regulator_probe,
};

module_platform_driver(da2083_regulator_driver);

MODULE_AUTHOR("Dialog Semiconductor");
MODULE_DESCRIPTION("Regulator driver for Dialog DA2083 PMIC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da2083-regulator");
