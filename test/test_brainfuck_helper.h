#ifndef TEST_BRAINFUCK_HELPER_H
#define TEST_BRAINFUCK_HELPER_H


/**
 * @brief Test get_input_prog function
 *
 * This function tests the get_input_prog function by checking if it returns the expected output for a given input file.
 *
 * @param void
 * @return void
 */
void test_get_input_prog(void);



/**
 * @brief Test free_input_prog function
 *
 * This function verifies tests the free_input_prog function by checking if the memory state before calling the get_input_prog function remains unchanged after deallocating memory with free_input_prog.
 *
 * @param void
 * @return void
 */
void test_free_input_prog();

/**
 * @brief Test build_loops function
 *
 * This function tests the build_loops function by checking if it constructs the loop structure correctly based on the input program.
 * It verifies the start pointer of the program, the offset values for loop positions, and the correct adding of the bracket markers.
 *
 * @param void
 * @return void
 */
void test_build_loops();

/**
 * @brief Test execute_instruction function
 *
 * This function tests the execute_instruction function by simulating all the Brainfuck instructions execution.
 *
 * @param void
 * @return void
 */
void test_execute_instruction();

#endif                          /*TEST_BRAINFUCK_HELPER_H */
