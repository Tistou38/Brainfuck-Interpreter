#include <stdio.h>
#include <stdint.h>
#include "brainfuck_debug.h"

void display_buffer(char *buffer)
{
    uint32_t i = 0;
    char current;
    while ((i < DATA_ARRAY_SIZE) && ((current = buffer[i]) != '\0')) {
        printf("current[%d] : %c\n", i, current);
        i++;
    }
}

void display_loops_array(struct Bracket *loops)
{
    struct Bracket current_loop;
    uint32_t i = 0;
    while ((loops[i].offset) != -1) {
        current_loop = loops[i];
        printf("Loop n°%d : offset = %d\n", i, current_loop.offset);
        i++;
    }
}
