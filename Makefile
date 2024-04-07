CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=brainfuck_interpreter
UNITY_ROOT=./Unity
TESTS_FILES=test_bf_files/affiche_1entree.bf test_bf_files/hello1.bf test_bf_files/hello2.bf test_bf_files/print3.bf test_bf_files/testko1.bf test_bf_files/tictactoe.bf
SRC_DIR=./src
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src

# List of source files (in /src)
SRC_FILES = $(SRC_DIR)/brainfuck_helper.c $(SRC_DIR)/brainfuck_main.c $(SRC_DIR)/brainfuck_debug.c

UNITARY_TEST_SRC1=test/test_brainfuck_helper.c $(SRC_DIR)/brainfuck_helper.c
TMP_TEST_DIR = test/tmp
# List of object files
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))

all: $(EXEC)
$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation rule for each .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


test_brainfuck_helper: $(UNITARY_TEST_SRC1) $(UNITY_ROOT)/src/unity.c
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $^

all_bf_files_test: $(EXEC)
	@for test_file in $(TESTS_FILES); do \
		echo "Running test: $$test_file"; \
		./$(EXEC) $$test_file; \
	done

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o


.PHONY: clean_tmp_test
clean_tmp_test:
	rm -f $(TMP_TEST_DIR)/*.bf

