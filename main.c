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

/**
 * config
 */

static char *_secret = "";
static char *_whitelists_in = "22";
static char *_ip_in = "";
static int _port = 9999;

module_param_named(secret, _secret, charp, 0000);
MODULE_PARM_DESC(secret, "shared key of remote connection encryption");
module_param_named(skip_ports, _whitelists_in, charp, 0440);
MODULE_PARM_DESC(skip_ports, "skipped ports, command seperated, ranges are allowed with format '1-1024'");
module_param_named(ip, _ip_in, charp, 0440);
MODULE_PARM_DESC(ip, "public ip of this server");
module_param_named(port, _port, int, 0440);
MODULE_PARM_DESC(port, "listening port of remote connection");

/**
 * variables
 */

static struct sn_whitelist *_whitelists;
static int _whitelists_len;
static __be32 _ip;

/**
 * entrypoint
 */

static int init_standnat(void)
{
    // validate and decode params
    int ret = 0;
    if ((_ip = in_aton(_ip_in)) == 0) {
        elog("failed to initialize, invalid param ip=%s", _ip_in);
        ret = -1;
        goto exit;
    }
    if (0 != (ret = init_filter(_whitelists, _whitelists_len, _ip)))
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
