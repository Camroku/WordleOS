/*
    This file is part of OSDEV Wordle.

    OSDEV Wordle is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version
    3 of the License, or (at your option) any later version.

    OSDEV Wordle is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with OSDEV Wordle. If not, see
    <https://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stddef.h>
#include <wordle/io.h>
#include <wordle/wordle.h>
#include <wordle/random.h>
#include <stdio.h>

uint16_t seed;

MODULE("random");

void random_seed()
{
    LOG("Initializing...");
    uint16_t rseed = 0;
    // seconds
    outb(0x70, 0x00);
    rseed += inb(0x71);
    // minutes
    outb(0x70, 0x02);
    rseed += inb(0x71);
    // hours
    outb(0x70, 0x04);
    rseed += inb(0x71);
    // week day
    outb(0x70, 0x06);
    rseed += inb(0x71);
    // days
    outb(0x70, 0x07);
    rseed += inb(0x71);
    // months
    outb(0x70, 0x08);
    rseed += inb(0x71);
    // years
    outb(0x70, 0x09);
    rseed += inb(0x71);
    // some numbers and operations that i randomly thought of
    seed = rseed * 16742;
    seed = ((seed * seed) << 2) * seed % 48525;
    LOG("Initialized...");
}

int get_random(uint16_t min, uint16_t max)
{
    uint16_t diff = max - min;
    seed++;
    seed = seed * 16742;
    seed = ((seed * seed) << 2) * seed % 48525;
    return (seed % diff) + min;
}
