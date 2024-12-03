/*
 * Copyright (c) 2024, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/logging/log.h>

#define GNSS_MODEM DEVICE_DT_GET(DT_ALIAS(gnss))

LOG_MODULE_REGISTER(gnss_sample, CONFIG_GNSS_LOG_LEVEL);

static const struct device *gnss_dev = DEVICE_DT_GET(DT_ALIAS(gnss));

static void gnss_data_cb(const struct device *dev, const struct gnss_data *data)
{
	if (data->info.fix_status != GNSS_FIX_STATUS_NO_FIX) {
		printf("Got a fix!\n");
	}
}
GNSS_DATA_CALLBACK_DEFINE(GNSS_MODEM, gnss_data_cb);

#if CONFIG_GNSS_SATELLITES
static void gnss_satellites_cb(const struct device *dev, const struct gnss_satellite *satellites,
			       uint16_t size)
{
	unsigned int tracked_count = 0;

	for (unsigned int i = 0; i != size; ++i) {
		tracked_count += satellites[i].is_tracked;
	}
	printf("%u satellite%s reported (of which %u tracked)!\n", size, size > 1 ? "s" : "",
	       tracked_count);
}
#endif
GNSS_SATELLITES_CALLBACK_DEFINE(GNSS_MODEM, gnss_satellites_cb);

int main(void)
{

	if (!device_is_ready(gnss_dev)) {
		printk("GNSS Device %s is not ready\n", gnss_dev->name);
		return 1;
	}

	while (1) {
		k_sleep(K_MSEC(1000));
	}
}
