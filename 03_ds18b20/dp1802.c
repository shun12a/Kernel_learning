#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

struct ds18b20_data {
    dev_t dev_num;
    
};

struct ds18b20_data *ds18b20;

int ds18b20_probe(struct platform_device *dev)
{
    printk("This is probe\n");

    ds18b20 = kmalloc(sizeof(ds18b20), GFP_KERNEL);
    if(ds18b20 < 0)
        printk("kmalloc init error\n");
    return 0;
}

static struct of_device_id ds18b20_match_table[] = {
    {.compatible = "alientek, ds18b20"},
    {},
};

struct platform_driver ds18b20_drv = {
    .probe = ds18b20_probe,
    .driver = {
        .name = "ds18b20",
        .owner = THIS_MODULE,
        .of_match_table = ds18b20_match_table,
    },
};

static int ds18b20_open (struct inode *dev, struct file *filt)
{
    return 0;
}

ssize_t ds18b20_read (struct file *filt, char __user *usrd, size_t dtr, loff_t *ll)
{
    return 0;
}

const struct file_operations fops = {
    .open = ds18b20_open,
    .read = ds18b20_read,
//    .write = ds18b20_write,

};

static int __init ds18b20_init(void)
{
    
    int ret;
    printk("ds18b20 modules init\n");
    ret = platform_driver_register(&ds18b20_drv);
    if(ret < 0)
        printk("platform_driver_register regoster error\n");
    return 0;
}

static void __exit ds18b20_exit(void)
{
    printk("ds18b20 modules exit\n");
    platform_driver_unregister(&ds18b20_drv);
}

module_init(ds18b20_init);
module_exit(ds18b20_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("alientek");