/**
 * filter.c
 *
 * packet filter using Netfilter
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

#include "filter.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static unsigned int hook_func(void *, struct sk_buff *, const struct nf_hook_state *);

static struct nf_hook_ops _nf_hook = {
    .hook = hook_func,
    .hooknum = NF_INET_PRE_ROUTING,
    .pf = PF_INET,
    .priority = NF_IP_PRI_FIRST};

static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    return NF_ACCEPT;
}

int init_filter(void)
{
    return nf_register_hook(&_nf_hook);
}

void deinit_filter(void)
{
    nf_unregister_hook(&_nf_hook);
}