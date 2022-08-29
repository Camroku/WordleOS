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

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <wordle/keyboard.h>
#include <wordle/wordle.h>
#include <wordle/initrd.h>
#include <wordle/terminal.h>
#include <wordle/vga.h>
#include <wordle/io.h>
#include <wordle/random.h>

MODULE("game");

void start_game(void)
{
    char word[5] = {0};
    char inpt[5] = {0};
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
    char *wordlist = initrd_read();
    char *wordp = wordlist + (get_random(0, 5756) * 5);
    for (int i = 0; i < 5; i++)
    {
        word[i] = wordp[i];
    }
    printf(
        "\033[0;31m+------------------------------------------------------------------------------+"
        "|                                 Wordle OS                                    |"
        "|                                                                              |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                 \033[1;37m_ _ _ _ _\033[0;31m                                    |"
        "|                                                                              |"
        "|                                 \033[1;32m? ? ? ? ?\033[0;31m                                    |"
        "|                                                                              |"
        "|                                Attempts: ?                                   |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "|                                                                              |"
        "| https://github.com/Camroku/WordleOS                     Made by Camroku.TECH |"
        "+------------------------------------------------------------------------------+\033[1;37m");
    int guess;
    bool correct = false;
    for (guess = 1; guess < 7 && !correct; guess++)
    {
        terminal_move_cursor_to(2 + guess, 34);
        terminal_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        for (int i = 0; i < 6;)
        {
            if (i != 5) {
                inpt[i] = keyboard_getchar();
                if (inpt[i] == '\b' && i > 0)
                {
                    inpt[i] = 0;
                    terminal_x_move(-2);
                    printf("_ ");
                    terminal_x_move(-2);
                    i--;
                }
                else if (((inpt[i] >= 'a' && inpt[i] <= 'z') || (inpt[i] >= 'A' && inpt[i] <= 'Z')) && i < 5){
                    printf("%c ", inpt[i]);
                    i++;
                }
            }
            else {
                switch (keyboard_getchar())
                {
                    case '\b':
                        inpt[i-1] = 0;
                        terminal_x_move(-2);
                        printf("_ ");
                        terminal_x_move(-2);
                        i -= 2;
                        break;
                    case '\n':
                        i++;
                        break;
                }
            }
        }
        terminal_move_cursor_to(2 + guess, 34);
        correct = true;
        for (int i = 0; i < 5; i++)
        {
            if (inpt[i] == word[i])
            {
                printf("\033[0;32m%c ", inpt[i]);
            }
            else
            {
                correct = false;
                bool found = false;
                for (int j = 0; j < 5; j++)
                {
                    if (inpt[i] == word[j])
                    {
                        printf("\033[1;33m%c ", inpt[i]);
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    printf("\033[1;37m%c ", inpt[i]);
                }
            }
        }
    }
    guess--;
    terminal_move_cursor_to(12, 43);
    printf("%d", guess);
    terminal_move_cursor_to(14, 35);
    if (correct)
        printf("\033[1;32mVICTORY\033[1;37m");
    else
        printf("\033[0;31mFAILURE\033[1;37m");
    terminal_move_cursor_to(10, 34);
    for (int i = 0; i < 5; i++)
    {
        printf("\033[1;37m%c ", word[i]);
    }
}


/*

*/