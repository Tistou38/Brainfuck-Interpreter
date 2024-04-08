# Brainfuck Interpreter 

Brainfuck Interpreter is a simple yet efficient interpreter for Brainfuck files. This project was developed as part of the preparatory course in the C language during the first year at Ensimag.


## Usage

```bash
## Compile the interpreter executable
make brainfuck_interpreter

# Interpret a Brainfuck file (file.bf)
./brainfuck_interpreter file.bf

# Execute unit tests
make test_brainfuck_helper
./test_brainfuck

# Interpret all Brainfuck files in the test_bf_files/ directory
make all_bf_files_test

# Clean up .o files and remove files in test/tmp
make clean
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

Baptiste Le Duc - MIT License