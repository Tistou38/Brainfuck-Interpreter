#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "unity.h"
#include "brainfuck_helper.h"

/* Prototypes des fonctions de test */
void test_get_input_prog();
void test_build_loops();
void test_execute_instruction();

/* Fonction d'initialisation du test suite */
void setUp(void) {}

/* Fonction de nettoyage du test suite */
void tearDown(void) {}



/* Test pour get_input_prog */
void test_get_input_prog() 
{
    FILE *test_file = fopen("test_bf_files/test_input_prog.bf", "w");
    fprintf(test_file, "[This is a test comment]");
    fclose(test_file);

    char *result = get_input_prog("test_bf_files/test_input_prog.bf");
    const char *expected = "[This is a test comment]";
    TEST_ASSERT_EQUAL_STRING(expected, result);
    TEST_ASSERT_EQUAL_CHAR(result[24], '\0');
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

    TEST_ASSERT_EQUAL(7, loops.loops_infos[0].offset);
    TEST_ASSERT_EQUAL(-1, loops.loops_infos[3].offset);

    free_loops(loops);
}

/* Test pour execute_instruction */
void test_execute_instruction() {
    char input_prog[] = "+.";
    struct Loops loops = build_loops(input_prog);
    char *ipp = input_prog;
    uint8_t data = 0;
    uint8_t *dpp = &data;
    execute_instruction(&ipp, &dpp, loops);

    TEST_ASSERT_EQUAL(1, data);

    free_loops(loops);
}

int main() {
    UNITY_BEGIN();

    /* Ajout des tests à l'exécution */
    RUN_TEST(test_get_input_prog);
    RUN_TEST(test_free_input_prog);

    return UNITY_END();
}