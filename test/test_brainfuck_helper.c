#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "unity.h"
#include "brainfuck_helper.h"


void setUp(void) {}

void tearDown(void) {}



/* Test pour get_input_prog */
void test_get_input_prog() 
{
    FILE *test_file = fopen("test_bf_files/test_input_prog.bf", "w");
    fprintf(test_file, "[ This is a test comment],>");
    fclose(test_file);

    char *result = get_input_prog("test_bf_files/test_input_prog.bf");
    const char *expected = "[],>";
    TEST_ASSERT_EQUAL_STRING(expected, result);
    TEST_ASSERT_EQUAL_CHAR(result[27], '\0');
    free(result);
}

void test_free_input_prog()
{
    /* Get memory usage information before allocation */
    struct mallinfo2 mallinfo_before = mallinfo2();
    char * ip = get_input_prog("test_bf_files/test_input_prog.bf");

    /* Get memory usage information after allocation */
    struct mallinfo2 mallinfo_after = mallinfo2();

    /* Check that memory was successfully allocated (keepcosts changed) */
    /* "keepcost" refers to the total amount of releasable free space at the top of the heap.
       If allocation happened, we expect the keepcost value to change because memory was consumed. */
    TEST_ASSERT_NOT_EQUAL_size_t(mallinfo_before.keepcost, mallinfo_after.keepcost);
    free_input_prog(ip);
    mallinfo_after = mallinfo2();

    /* Check that memory was successfully freed (keepcosts are the same as before allocation) */
    TEST_ASSERT_EQUAL_size_t(mallinfo_before.keepcost, mallinfo_after.keepcost);
}

/* Test pour build_loops */
void test_build_loops() {
    char input_prog[] = "[>++<-]";
    struct Loops loops = build_loops(input_prog);

    TEST_ASSERT_EQUAL_PTR(input_prog, loops.start_prog);

    TEST_ASSERT_EQUAL(6, loops.loops_infos[0].offset);
    TEST_ASSERT_EQUAL(6, loops.loops_infos[6].offset);

    /*Test that bracket marker has been correctly added*/
    TEST_ASSERT_EQUAL(-1, loops.loops_infos[7].offset);
}

/* Test pour execute_instruction */
void test_execute_instruction() {
    FILE *test_file = fopen("test_bf_files/test_execute_instruction.bf", "w");
    fprintf(test_file, "[This is a file used in test_brainfuck_helper.c to test execute_instruction]\n,.>++[-]<");
    fclose(test_file);

    char * input_prog = get_input_prog("test_bf_files/test_execute_instruction.bf");
    struct Loops loops = build_loops(input_prog);
    char *ip = input_prog;
    uint8_t * data_array = calloc(DATA_ARRAY_SIZE, sizeof(uint8_t));;
    uint8_t *dp = data_array;

    /* Test 'initial comment loop' */
    char * ip_before = ip;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(ip_before+3, ip); /* Test '.' in the initial comment loop is correctly ignored*/
    
    /* Test ',' instruction */
    freopen("test/test_coma.txt", "r", stdin);
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL(54, *dp);

    /* Test '.' instruction */
    freopen("test/test_point.txt", "w", stdout);
    execute_instruction(&ip, &dp, loops);
    freopen("/dev/tty", "w", stdout); /* Restablished original stdout*/
    FILE *file = fopen("test/test_point.txt", "r");
    uint32_t stdout_value;
    fscanf(file, "%d", &stdout_value);
    TEST_ASSERT_EQUAL(6, stdout_value);
   
    /* Test '>' instruction */
    uint8_t *dp_before = dp;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(dp_before+1, dp);

    /* Test '+++' instruction*/
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL(1, *dp);
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL(2, *dp);


    /* Test '[' instruction */
    ip_before = ip;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(ip_before + 1, ip);

    /* Test '-' instruction */
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL(1, *dp);

    /* Test ']' instruction */
    ip_before = ip;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(ip_before - 1, ip);

    /* Test '-' instruction */
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL(0, *dp);

    /* Test ']' instruction */
    ip_before = ip;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(ip_before + 1, ip);

    /* Test '<' instruction */
    dp_before = dp;
    execute_instruction(&ip, &dp, loops);
    TEST_ASSERT_EQUAL_PTR(dp_before - 1, dp);

    // execute_instruction(&ip, &dp, loops);
    // TEST_ASSERT_EQUAL(1, *dp);

    // execute_instruction(&ip, &dp, loops);
    // TEST_ASSERT_EQUAL(0, *dp);
    
    // execute_instruction(&ip, &dp, loops);
    // TEST_ASSERT_EQUAL(1, *dp);

    // execute_instruction(&ip, &dp, loops);
    // TEST_ASSERT_EQUAL(0, *dp);
    

    free_loops(loops);
}

int main() {
    UNITY_BEGIN();

    /* Ajout des tests à l'exécution */
    RUN_TEST(test_get_input_prog);
    RUN_TEST(test_free_input_prog);
    RUN_TEST(test_build_loops);
    test_execute_instruction();
    return UNITY_END();
}