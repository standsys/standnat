/**
 * config.h
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

#ifndef _STANDNAT_CONFIG_H_
#define _STANDNAT_CONFIG_H_

#define SN_NAME "standnat"
#define SN_VERSION "1.0"

#define SN_MAX_IGNORED_PORT_RANGES 11

#include <linux/types.h>

/**
 * config structure
 */
struct sn_config
{
    char *secret;
    __be32 address;
    unsigned short port;
    unsigned short ignores[SN_MAX_IGNORED_PORT_RANGES * 2];
};

struct sn_config *init_config(void);

#endif
