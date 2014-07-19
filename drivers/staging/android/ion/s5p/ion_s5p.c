/*
* drivers/staging/android/ion/s5p/ion_s5p.c
*
* Copyright (C) 2011 Google, Inc.
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
*/

#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/module.h>
#include "../ion.h"
#include "../ion_priv.h"

struct ion_device *s5p_ion_device;
EXPORT_SYMBOL(s5p_ion_device);

static int num_heaps;
static struct ion_heap **heaps;

static int s5p_ion_probe(struct platform_device *pdev)
{
	struct ion_platform_data *pdata = pdev->dev.platform_data;
	int err;
	int i;

	pr_info("[ion-s5p] %s\n", __func__);

	num_heaps = pdata->nr;
	heaps = kzalloc(sizeof(struct ion_heap *) * pdata->nr, GFP_KERNEL);
	if (!heaps)
		return -ENOMEM;

	s5p_ion_device = ion_device_create(NULL);

	if (IS_ERR_OR_NULL(s5p_ion_device)) {
		kfree(heaps);
		return PTR_ERR(s5p_ion_device);
	}

	/* create the heaps as specified in the board file */
	for (i = 0; i < num_heaps; i++) {
		struct ion_platform_heap *heap_data = &pdata->heaps[i];

		heaps[i] = ion_heap_create(heap_data);

		if (IS_ERR_OR_NULL(heaps[i])) {
			err = PTR_ERR(heaps[i]);
			goto err;
		}

		ion_device_add_heap(s5p_ion_device, heaps[i]);
		pr_info("[ion-s5p] %s: adding heap %s of type %d with %lx@%x\n",
			__func__, heap_data->name, heap_data->type,
			heap_data->base, heap_data->size);
	}

	platform_set_drvdata(pdev, s5p_ion_device);
	return 0;

err:

	for (i = 0; i < num_heaps; i++) {
		if (heaps[i])
			ion_heap_destroy(heaps[i]);
	}

	kfree(heaps);
	return err;
}

static int s5p_ion_remove(struct platform_device *pdev)
{
	struct ion_device *idev = platform_get_drvdata(pdev);
	int i;

	ion_device_destroy(idev);
	pr_info("[ion-s5p] %s\n", __func__);

	for (i = 0; i < num_heaps; i++)
		ion_heap_destroy(heaps[i]);

	kfree(heaps);
	return 0;
}

static struct platform_driver ion_driver = {
	.probe = s5p_ion_probe,
	.remove = s5p_ion_remove,
	.driver = { .name = "ion-s5p" }
};

static int __init ion_init(void)
{
	return platform_driver_register(&ion_driver);
}

static void __exit ion_exit(void)
{
	platform_driver_unregister(&ion_driver);
}

module_init(ion_init);
module_exit(ion_exit);
