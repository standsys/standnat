/**
 * config.c
 *
 * version information
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
#include "utils.h"

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/inet.h>

MODULE_VERSION(SN_VERSION);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yanke Guo <ryan@islandzero.net>");
MODULE_DESCRIPTION(SN_NAME " v" SN_VERSION ", kernel module for StandSys remote full-mapping NAT");

static struct sn_config _config;

static char *_secret_in = "";
static char *_address_in = "";
static int _port_in = 9999;
static char *_ignore_in = "22";

module_param_named(secret, _secret_in, charp, 0000);
MODULE_PARM_DESC(secret, "encryption key for remote connections");
module_param_named(address, _address_in, charp, 0440);
MODULE_PARM_DESC(address, "public ip of this server");
module_param_named(port, _port_in, int, 0440);
MODULE_PARM_DESC(port, "listening port for remote connections");
module_param_named(ignore, _ignore_in, charp, 0440);
MODULE_PARM_DESC(ignore, "ignored ports, max 10 items, command seperated, ranges are supported with format '1-1024'");

struct sn_config *init_config(void)
{
    int igc, igi;
    // secret
    if ((_config.secret = _secret_in) == NULL || strlen(_secret_in) == 0)
    {
        elog("invalid param 'secret', cannot be zero-length");
        return NULL;
    }
    dlog("'secret' set with length %d", (int)strlen(_config.secret));
    // address
    if (_address_in == NULL || (_config.address = in_aton(_address_in)) == 0)
    {
        elog("invalid param 'address', cannot be empty or 0");
        return NULL;
    }
    dlog("'address' set to %d", _config.address);
    // port
    if (_port_in < 1 || _port_in > PORT_MAX)
    {
        elog("invalid param 'port'");
        return NULL;
    }
    _config.port = (unsigned short)_port_in;
    dlog("'port' set to %d", _config.port);
    // ignore
    memset(_config.ignores, 0, sizeof(_config.ignores));
    igc = decode_ignored_ports(_ignore_in, (unsigned short *)_config.ignores, (SN_MAX_IGNORED_PORT_RANGES - 1) * 2);
    if (igc < 0)
    {
        elog("invalid param 'ignore'");
        return NULL;
    }
    _config.ignores[igc] = _config.port;
    _config.ignores[igc + 1] = _config.port;
    // filp from/to if needed
    for (igi = 0; igi < SN_MAX_IGNORED_PORT_RANGES; igi++)
    {
        if (_config.ignores[igi * 2] > _config.ignores[igi * 2 + 1])
        {
            unsigned short v = _config.ignores[igi * 2];
            _config.ignores[igi * 2] = _config.ignores[igi * 2 + 1];
            _config.ignores[igi * 2 + 1] = v;
        }
    }
        // TODO: compact _config.ignores
#ifdef DEBUG
    for (igi = 0; igi < SN_MAX_IGNORED_PORT_RANGES; igi++)
    {
        dlog("'ignored' added with %d - %d", _config.ignores[igi * 2], _config.ignores[igi * 2 + 1]);
    }
#endif
    return &_config;
}
