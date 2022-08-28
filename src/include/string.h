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
#include <stddef.h>

size_t strlen(const char *str);
int strcmp(char *str1, char *str2);
void strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
void *memcpy(void *dest, const void *src, size_t len);
void *memset(void *dest, int val, size_t len);
