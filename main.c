/*
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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/*
 * module information
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yanke Guo <ryan@islandzero.net>");
MODULE_DESCRIPTION("Linux kernel module for StandSys remote full-mapping NAT");

/*
 * definition
 */
#define SUCCESS 0

/*
 * entrypoint
 */

static int __init init_standnat(void)
{
    printk(KERN_INFO "standnat initialized\n");
    return SUCCESS;
}

static void __exit deinit_standnat(void)
{
    printk(KERN_INFO "standnat deinitialized\n");
    return;
}

module_init(init_standnat);
module_exit(deinit_standnat);