/* drivers/input/misc/sn65dsi8x.c
 *
 *  Compatible with: sn65dsi83, sn65dsi84, sn65dsi85
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

#include <linux/hrtimer.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/version.h>
#include <linux/jiffies.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/byteorder/generic.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/notifier.h>
#include <linux/fb.h>

#include "sn65dsi8x.h"

struct sn65dsi8x_t
{
	int reset_gpio;
	int display_reset_gpio;
	struct i2c_client *client;
	struct sn65dsi8x_params_t *params;
};

static int sn65dsi8x_parse_dt(struct sn65dsi8x_t *lvds_bridge)
{
	struct device_node *node;
	struct device *dev;
	int ret = 0;

	dev = &lvds_bridge->client->dev;
	if (!dev)
	{
		pr_err("%s: Cannot find any devices in device tree\n", __func__);
		return -ENODEV;
	}

	node = dev->of_node;

	/* Get reset gpio of LVDS bridge IC */
	lvds_bridge->reset_gpio = of_get_named_gpio(node, "ti,reset-gpio", 0);
	if (!gpio_is_valid(lvds_bridge->reset_gpio))
	{
		pr_err("%s: Invalid GPIO, reset-gpio: %d\n", __func__, lvds_bridge->reset_gpio);
		return -EINVAL;
	}
	/* Request reset gpio of LVDS bridge IC */
	ret = gpio_request(lvds_bridge->reset_gpio, "ti-reset-gpio");
	if (ret)
	{
		pr_err("%s: request ti,reset-gpio failed, ret=%d\n", __func__, ret);
		return -EINVAL;
	}

	/* Get reset gpio of LCD panel */
	lvds_bridge->display_reset_gpio = of_get_named_gpio(node, "qcom,platform-reset-gpio", 0);
	if (!gpio_is_valid(lvds_bridge->display_reset_gpio))
	{
		pr_err("%s: Invalid GPIO, display_reset_gpio: %d\n", __func__, lvds_bridge->display_reset_gpio);
		goto display_reset_gpio_err;
	}
	/* Request reset gpio of LCD panel */
	ret = gpio_request(lvds_bridge->display_reset_gpio, "display-reset-gpio");
	if (ret)
	{
		pr_err("%s: request display-reset-gpio failed, ret=%d\n", __func__, ret);
		goto display_reset_gpio_err;
	}

	/* Success */
	return 0;

	/* Error */
display_reset_gpio_err:
	gpio_free(lvds_bridge->reset_gpio);
	return -EINVAL;
}

static int sn65dsi8x_i2c_write(struct i2c_adapter *adap, u8 adr, u8 *data, int len)
{
	int ret;
	struct i2c_msg msg = { 
		.addr = adr, 
		.flags = 0,
		.buf = data, 
		.len = len 
	};

	ret = i2c_transfer(adap, &msg, 1);
	if (ret != 1) 
		return -EIO;
	if (ret < 0)
		return ret;
	
	return 0;
}

static int sn65dsi8x_i2c_write_reg(struct i2c_client *client, u8 reg, u8 val)
{
	u8 msg[2] = { reg, val };

	return sn65dsi8x_i2c_write(client->adapter, client->addr, msg, 2);
}

static int sn65dsi8x_write_settings(struct i2c_client *client, struct sn65dsi8x_params_t *params)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sn65dsi8x_parameters); i++ )
	{
		ret = sn65dsi8x_i2c_write_reg(client, params[i].reg, params[i].value);
		if (ret) 
		{
			pr_err("%s: Failed to write i2c data at reg = 0x%x, value = 0x%x \n", __func__, params[i].reg, params[i].value);
			return -EINVAL;
		}
	}

	return ret;

}

static int sn65dsi8x_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct sn65dsi8x_t lvds_bridge;
	int ret = 0;

	lvds_bridge.params = sn65dsi8x_parameters;
	lvds_bridge.client = client;

	/* Parse device tree */
	ret = sn65dsi8x_parse_dt(&lvds_bridge);
	if (ret)
	{
		pr_err("%s: Failed to parse device tree, ret=%d\n", __func__, ret);
		return -EINVAL;
	}

	/* Write settings LVDS Bridge IC */
	ret = sn65dsi8x_write_settings(lvds_bridge.client, lvds_bridge.params);
	if (ret)
	{
		pr_err("%s: Failed to write settings sn65dsi8x, ret=%d\n", __func__, ret);
		return -EINVAL;
	}

	/* Start LVDS Bridge IC */
	

	return 0;
}

static int sn65dsi8x_remove(struct i2c_client *client)
{
	return 0;
}

static const struct of_device_id sn65dsi8x_match_table[] = {
	{
		.compatible = "ti,sn65dsi8x",
	},
	{},
};

static const struct i2c_device_id sn65dsi8x_id[] = {
	{"sn65dsi8x", 0},
	{}
};

static struct i2c_driver sn65dsi8x_driver = {
	.probe = sn65dsi8x_probe,
	.remove = sn65dsi8x_remove,
	.id_table = sn65dsi8x_id,
	.driver = {
		.name = "sn65dsi8x",
		.owner = THIS_MODULE,
		.of_match_table = sn65dsi8x_match_table,
	},
};

static int __init sn65dsi8x_init(void)
{
	return i2c_add_driver(&sn65dsi8x_driver);
}

static void __exit sn65dsi8x_exit(void)
{
	i2c_del_driver(&sn65dsi8x_driver);
}

module_init(sn65dsi8x_init);
module_exit(sn65dsi8x_exit);

MODULE_AUTHOR("Quang Nguyen <quang.ng193@gmail.com>");
MODULE_DESCRIPTION("sn65dsi8x Driver");
MODULE_LICENSE("GPL");
