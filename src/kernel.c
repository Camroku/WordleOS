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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wordle/terminal.h>
#include <wordle/dt.h>
#include <wordle/timer.h>
#include <wordle/keyboard.h>
#include <wordle/serial.h>
#include <wordle/io.h>
#include <wordle/game.h>
#include <wordle/wordle.h>
#include <wordle/multiboot.h>
#include <wordle/initrd.h>
#include <wordle/random.h>

MODULE("kernel");

/* Wordle OS Kernel main function */
void kernel_main(uint32_t magic, uint32_t addr)
{
    serial_init();
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        LOG("Multiboot magic number is invalid!");
        for (;;)
            ;
    }
    multiboot_info_t *mbi_ptr = (multiboot_info_t *)addr;

    multiboot_module_t *module_ptr = (multiboot_module_t *)mbi_ptr->mods_addr;
    mb_module_count = mbi_ptr->mods_count;
    for (uint32_t i = 0; i < mb_module_count; i++)
    {
        mb_module_names[i] = (char *)module_ptr[i].cmdline;
        if (strcmp((char *)module_ptr->cmdline, "wordlist") == 0)
        {
            initrd_init(module_ptr->mod_start, module_ptr->mod_end);
        }
    }
    LOG("Initializing");
    init_descriptor_tables();
    terminal_initialize();
    timer_init(1000);
    keyboard_init();
    random_seed();
    LOG("Initialized");
    LOG("Starting game");
    start_game();
}
