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

#include <linux/module.h>

MODULE_VERSION(SN_VERSION);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yanke Guo <ryan@islandzero.net>");
MODULE_DESCRIPTION(SN_NAME " v" SN_VERSION ", kernel module for StandSys remote full-mapping NAT");
