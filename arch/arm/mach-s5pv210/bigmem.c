/*
 * Copyright (C)  20012 stratosk <stratosk@semaphore.gr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

extern bool bigmem;

/* sysfs interface */
static ssize_t enable_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", bigmem?1:0);
}

static ssize_t enable_store(struct kobject *kobj, struct kobj_attribute *attr,
        const char *buf, size_t count)
{
    int input;
    sscanf(buf, "%du", &input);
    bigmem = input;
    return count;
}

static struct kobj_attribute enable_attribute =
    __ATTR(enable, 0666, enable_show, enable_store);

static struct attribute *attrs[] = {
    &enable_attribute.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject *enable_kobj;

static int __init bigmem_init(void)
{
    int retval;

    enable_kobj = kobject_create_and_add("bigmem", kernel_kobj);
    if (!enable_kobj) {
        return -ENOMEM;
    }
    retval = sysfs_create_group(enable_kobj, &attr_group);
    if (retval)
        kobject_put(enable_kobj);
    return retval;
}
/* end sysfs interface */

static void __exit bigmem_exit(void)
{
    kobject_put(enable_kobj);
}

MODULE_AUTHOR("stratosk <stratosk@semaphore.gr>");
MODULE_DESCRIPTION("Bigmem");
MODULE_LICENSE("GPL");

module_init(bigmem_init);
module_exit(bigmem_exit);
