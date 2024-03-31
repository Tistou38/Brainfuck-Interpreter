#ifndef BRAINFUCK_DEBUG_H
#define BRAINFUCK_DEBUG_H

#include <stdlib.h>
#include <stdint.h>
#include "brainfuck_helper.h"

/**
 * @brief Display buffer
 *
 * @param buffer 
 * @return void
 */
void display_buffer(char* buffer);

void display_loops_array(struct Bracket* loops);
#endif