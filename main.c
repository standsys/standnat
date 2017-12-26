/**
 * main.c
 *
 * entrypoint for kernel module
 *
 * Copyright (C) 2017 Yanke Guo <ryan@islandzero.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "filter.h"
#include "utils.h"

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/inet.h>

static struct sn_config *_config;

/**
 * entrypoint
 */

static int init_standnat(void)
{
    int ret = 0;
    if ((_config = init_config()) == NULL)
    {
        ret = -1;
        goto exit;
    }
    if (0 != (ret = init_filter(_config)))
    {
        goto exit;
    }
    dlog("initialized");
exit:
    return ret;
}

static void deinit_standnat(void)
{
    deinit_filter();
    dlog("deinitialized");
    return;
}

module_init(init_standnat);
module_exit(deinit_standnat);
