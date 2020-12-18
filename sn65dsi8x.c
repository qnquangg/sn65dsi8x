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

static int sn65dsi8x_parse_dt() {

}

static int sn65dsi8x_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    
    return 0;
}

static int sn65dsi8x_remove(struct i2c_client *client)
{
    return 0;
}

static const struct of_device_id sn65dsi8x_match_table[] = {
		{.compatible = "ti,sn65dsi8x",},
		{ },
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
