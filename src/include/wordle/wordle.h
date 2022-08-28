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

#pragma once
#include <stdint.h>
#include <wordle/serial.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))
#define MODULE(name) __attribute__((unused)) static char *__MODULE_NAME = name;
#define LOG(message)                 \
    write_serial('[');               \
    write_str_serial(__MODULE_NAME); \
    write_str_serial("]: ");         \
    write_str_serial(message);       \
    write_serial('\n');

void panic(const char *message, const char *file, uint32_t line);
void panic_assert(const char *file, uint32_t line, const char *desc);

uint32_t mb_module_count;
char **mb_module_names;
