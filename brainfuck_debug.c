#include <stdio.h>
#include <stdint.h>
#include "brainfuck_debug.h"

void display_buffer(char* buffer){
    uint32_t i = 0;
    char current;
    while((i < DATA_ARRAY_SIZE) && ((current = buffer[i]) != '\0')){
        printf("current[%d] : %c\n", i, current);
        i ++;
    }
}
void display_loops_array(struct Loop* loops){
    struct Loop current_loop;
    uint32_t i = 0;
    while ((loops[i].start) != -1)
    {
        current_loop = loops[i];
        printf("Loop n°%d : start = %d, end = %d\n", i, current_loop.start, current_loop.end);
        i++;
    }
}