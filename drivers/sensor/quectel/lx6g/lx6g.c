/*
 * Copyright (c) 2024, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT quectel_lx6g

#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "lx6g.h"

LOG_MODULE_REGISTER(LX6G, CONFIG_SENSOR_LOG_LEVEL);

struct lx6g_config {
};

struct lx6g_data {
};

static int lx6g_attr_set(const struct device *dev, enum sensor_channel chan,
			   enum sensor_attribute attr, const struct sensor_value *val)
{
	return 0;
}

static int lx6g_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
	struct lx6g_data *data = dev->data;
	const struct lx6g_config *config = dev->config;

	return 0;
}

static int lx6g_channel_get(const struct device *dev, enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct lx6g_data *data = dev->data;

	// TODO: Update val with the sensor value
	val->val1 = 0;
	val->val2 = 0;

	return 0;
}

static int lx6g_init(const struct device *dev)
{
	const struct lx6g_config *config = dev->config;
	struct lx6g_data *data = dev->data;

	return 0;
}

static const struct sensor_driver_api lx6g_driver_api = {
	.attr_set = lx6g_attr_set,
	.sample_fetch = lx6g_sample_fetch,
	.channel_get = lx6g_channel_get,
};

#define LX6G_INIT(n)                                                                             \
	static struct lx6g_config lx6g_config_##n = {                                             \
	};                                                                                         \
	static struct lx6g_data lx6g_data_##n;                                                 \
	DEVICE_DT_INST_DEFINE(n, lx6g_init, NULL, &lx6g_data_##n, &lx6g_config_##n,          \
			      POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &lx6g_driver_api);

DT_INST_FOREACH_STATUS_OKAY(LX6G_INIT)
