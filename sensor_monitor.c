#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static struct kobject *sensor_kobj;
static struct hrtimer sensor_timer;
static int temp_value = 25;
static int pressure_value = 1000;

enum hrtimer_restart sensor_timer_callback(struct hrtimer *timer)
{
    temp_value = 25 + (prandom_u32() % 10);       // Random temp: 25-34
    pressure_value = 1000 + (prandom_u32() % 20); // Random pressure: 1000-1019

    hrtimer_forward_now(timer, ms_to_ktime(5000)); // 5-second interval
    return HRTIMER_RESTART;
}

static ssize_t temp_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", temp_value);
}

static ssize_t pressure_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", pressure_value);
}

static struct kobj_attribute temp_attr = __ATTR_RO(temp);
static struct kobj_attribute pressure_attr = __ATTR_RO(pressure);

static int __init sensor_init(void)
{
    sensor_kobj = kobject_create_and_add("virtual_sensor", kernel_kobj);
    if (!sensor_kobj)
        return -ENOMEM;

    sysfs_create_file(sensor_kobj, &temp_attr.attr);
    sysfs_create_file(sensor_kobj, &pressure_attr.attr);

    hrtimer_init(&sensor_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    sensor_timer.function = &sensor_timer_callback;
    hrtimer_start(&sensor_timer, ms_to_ktime(5000), HRTIMER_MODE_REL);

    printk(KERN_INFO "Virtual Sensor Module loaded\n");
    return 0;
}

static void __exit sensor_exit(void)
{
    hrtimer_cancel(&sensor_timer);
    kobject_put(sensor_kobj);
    printk(KERN_INFO "Virtual Sensor Module unloaded\n");
}

module_init(sensor_init);
module_exit(sensor_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sriharan R M");
MODULE_DESCRIPTION("Virtual Sensor Kernel Module");

