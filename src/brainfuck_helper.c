#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include "brainfuck_helper.h"
#include <stdio.h>

char *get_input_prog(char *input_filename)
{
    char *array = malloc(DATA_ARRAY_SIZE * sizeof(char));

    /*Opened file in read mode */
    FILE *fptr;
    fptr = fopen(input_filename, "r"); 
    if (fptr == NULL){
        return NULL;  /*Case fptr = NULL handled by brainfuck_main */
    }

    uint32_t idx_file = 0;
    uint32_t idx_array = 0;
    int c;
    while ((idx_file < DATA_ARRAY_SIZE - 1) && ((c = fgetc(fptr)) != EOF)) {
        switch (c) {
        case POINT:
        case COMMA:
        case ADD:
        case SUB:
        case NEXT:
        case BACK:
        case OPEN_BRACKET:
        case CLOSE_BRACKET:
            array[idx_array] = (char) c;
            idx_array++;
            break;
        default:
            break;
        }

        idx_file++;
    }
    array[idx_array] = '\0';    /*Add end character */

    return array;

}

void free_input_prog(char *input_prog)
{
    if (input_prog != NULL) {
        free(input_prog);
        input_prog = NULL;
        return;
    }
}


struct Loops *build_loops(char *input_prog)
{
    struct Loops *loops = malloc(sizeof(struct Loops));
    loops->start_prog = input_prog;

    /* Allocate memory for loops_infos with initial capacity */
    uint32_t initial_capacity = DATA_ARRAY_SIZE * sizeof(struct Bracket);
    struct Bracket *loops_infos = malloc(initial_capacity);
    assert(loops_infos != NULL
           && "Failed to allocate space for loops_infos array");

    /* Allocate memory for stack with initial capacity */
    uint32_t *stack = malloc(DATA_ARRAY_SIZE * sizeof(uint32_t));
    if (stack == NULL) {
        fprintf(stderr, "Failed to allocate space for stack array\n");
        free(loops_infos);      /* Free previously allocated memory */
        exit(EXIT_FAILURE);
    }

    uint32_t top_stack = 0;
    char current;
    uint32_t i = 0;
    while ((current = input_prog[i]) != '\0') {
        if (current == '[') {
            stack[top_stack] = i;
            top_stack++;
        } else if (current == ']') {
            if (top_stack == 0) {
                /* Handle unmatched closing bracket */
                fprintf(stderr, "Unmatched closing bracket\n");
                free(loops_infos);
                free(stack);
                exit(EXIT_FAILURE);
            }

            uint32_t idx_open_bracket = stack[top_stack - 1];
            struct Bracket open_bracket = {.offset =
                    abs((int) (i - idx_open_bracket))
            };
            loops_infos[idx_open_bracket] = open_bracket;

            struct Bracket close_bracket = {.offset =
                    abs((int) (i - idx_open_bracket))
            };
            loops_infos[i] = close_bracket;
            top_stack--;
        }
        i++;
    }

    /* Add end marker loop */
    struct Bracket last_loop = {.offset = -1 };
    loops_infos[i] = last_loop;

    /* Reallocate memory to fit actual loop_infos size */
    uint32_t final_capacity = i * sizeof(struct Bracket);
    if (final_capacity < initial_capacity) {
        struct Bracket *tmp_loop = realloc(loops_infos, final_capacity);
        if (tmp_loop != NULL) {
            loops_infos = tmp_loop;
        }
    }

    /*Free stack memory after use */
    free(stack);
    loops->loops_infos = loops_infos;

    return loops;
}


void free_loops(struct Loops *loops)
{
    if (loops != NULL) {
        if (loops->loops_infos != NULL) {
            free(loops->loops_infos);
            loops->loops_infos = NULL;
        }
        free(loops);
        loops = NULL;
        return;
    }


}

void execute_instruction(char **ipp, uint8_t ** dpp, struct Loops *loops)
{

    switch (**ipp) {
    case ADD:
        (**dpp)++;
        break;
    case SUB:
        (**dpp)--;
        break;
    case NEXT:
        (*dpp)++;
        break;
    case BACK:
        (*dpp)--;
        break;
    case COMMA:
        (**dpp) = getchar();
        break;
    case POINT:
        putchar(**dpp);
        break;
    case OPEN_BRACKET:
        if (**dpp == 0) {
            (*ipp) =
                (*ipp) + loops->loops_infos[(*ipp) -
                                            loops->start_prog].offset;
        }
        break;
    case CLOSE_BRACKET:
        if (**dpp != 0) {
            (*ipp) =
                (*ipp) - loops->loops_infos[(*ipp) -
                                            loops->start_prog].offset;
        }
        break;
    default:
        fprintf(stderr,
                "[execute_instruction] Error while reading instruction '%c'",
                **ipp);
        break;
    }

    (*ipp)++;

}
