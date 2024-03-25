CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=brainfuck_interpreter
TESTS_FILES = test/affiche_1entree.bf test/hello1.bf test/hello2.bf test/print3.bf test/testko1.bf test/tictactoe.bf

all: $(EXEC)
brainfuck_interpreter: brainfuck_helper.o brainfuck_debug.o brainfuck_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

brainfuck_helper.o: brainfuck_helper.c
	$(CC) -o $@ -c $< $(CFLAGS)

brainfuck_debug.o: brainfuck_debug.c
	$(CC) -o $@ -c $< $(CFLAGS)

brainfuck_main.o: brainfuck_main.c
	$(CC) -o $@ -c $< $(CFLAGS)

all_test: $(EXEC) $(TESTS_FILES)
	@for test_file in $(TESTS_FILES); do \
		echo "Running test: $$test_file"; \
		./$(EXEC) $$test_file; \
	done
.PHONY: clean
clean:
	rm -f *.o

