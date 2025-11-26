// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * I2C interface for Dialog DA2083 PMIC
 *
 * Copyright (C) 2012 Dialog Semiconductor Ltd.
 * Copyright (C) 2025 (Mainline port)
 */

#include <linux/i2c.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regmap.h>

#include <linux/mfd/da2083/core.h>
#include <linux/mfd/da2083/registers.h>

static int da2083_i2c_probe(struct i2c_client *i2c)
{
	struct da2083 *da2083;
	int ret;

	da2083 = devm_kzalloc(&i2c->dev, sizeof(struct da2083), GFP_KERNEL);
	if (!da2083)
		return -ENOMEM;

	da2083->dev = &i2c->dev;
	da2083->irq = i2c->irq;

	i2c_set_clientdata(i2c, da2083);

	da2083->regmap = devm_regmap_init_i2c(i2c, &da2083_regmap_config);
	if (IS_ERR(da2083->regmap)) {
		ret = PTR_ERR(da2083->regmap);
		dev_err(&i2c->dev, "Failed to initialize regmap: %d\n", ret);
		return ret;
	}

	ret = da2083_device_init(da2083);
	if (ret)
		return ret;

	return 0;
}

static void da2083_i2c_remove(struct i2c_client *i2c)
{
	struct da2083 *da2083 = i2c_get_clientdata(i2c);

	da2083_device_exit(da2083);
}

static const struct of_device_id da2083_of_match[] = {
	{ .compatible = "dlg,da2083", },
	{ }
};
MODULE_DEVICE_TABLE(of, da2083_of_match);

static const struct i2c_device_id da2083_i2c_id[] = {
	{ "da2083", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, da2083_i2c_id);

static struct i2c_driver da2083_i2c_driver = {
	.driver = {
		.name = "da2083",
		.of_match_table = da2083_of_match,
	},
	.probe = da2083_i2c_probe,
	.remove = da2083_i2c_remove,
	.id_table = da2083_i2c_id,
};

module_i2c_driver(da2083_i2c_driver);

MODULE_DESCRIPTION("I2C support for Dialog DA2083 PMIC");
MODULE_AUTHOR("Dialog Semiconductor");
MODULE_LICENSE("GPL");
