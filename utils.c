/**
 * utils.c
 *
 * utils for standnat
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

#include "utils.h"

int sn_decode_ignore(char *s, unsigned short *ports, int ports_len)
{
    // count of port decoded, must be even
    int i = 0;
    // current port number
    int p;
    // check valid
    if (s == NULL)
        return -1;
    // must be even count
    if (ports_len == 0 || ports_len % 2 != 0)
        return -1;
    for (;;)
    {
        p = 0;
        // extract p
        while (*s >= '0' && *s <= '9')
        {
            p *= 10;
            p += (*s - '0');
            s++;
        }
        // validate p
        if (p < 1 || p > PORT_MAX)
            return -1;
        // assign p
        ports[i] = p;
        i++;
        // too much
        if (i >= ports_len)
            break;
        // detect '-', ',', '\0'
        if (*s == '-')
        {
            // '-' found at leading
            if (i % 2 == 0)
                return -1;
        }
        else if (*s == ',' || *s == '\0')
        {
            // ',' found with even number of ports, expand it
            if (i % 2 == 1)
            {
                ports[i] = ports[i - 1];
                i++;
            }
            // break if ends reached
            if (*s == '\0')
                break;
        }
        else
            // unknown char
            return -1;
        // move to next char
        s++;
    }
    return i;
}
