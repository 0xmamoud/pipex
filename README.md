# 🚀 Pipex

`Pipex` is a 42 project that recreates the shell's piping mechanism. It enables chaining multiple commands and passing the output of one command as the input to the next, simulating the behavior of the shell pipelines. This project helps to deepen your understanding of system calls like `pipe()`, `fork()`, `execve()`, and file descriptors.

---

## 🛠 Features

- **Single Pipeline**: Handles the execution of commands in a single pipeline, such as:
  ```bash
  ./pipex infile "cmd1" "cmd2" outfile
- **Equivalent to**:
    ```bash
    < infile cmd1 | cmd2 > outfile
- **Heredoc Support**: Supports heredoc functionality to take input directly from the terminal:
    ```bash
    ./pipex here_doc LIMITER "cmd1" "cmd2" outfile
- **Equivalent to**:
    ```bash
    << LIMITER cmd1 | cmd2 >> outfile
- **Robust Parsing**: Handles errors such as invalid paths, permission issues, and invalid commands.
- **Custom Library**: Relies on libft to simplify common operations.

## 🚀 Installation  

1. Clone the repository:  
   ```bash
    git clone https://github.com/yourusername/pipex.git
    cd pipex

2. Compile the library using the Makefile:
    ```bash
    make
3. Run the program
    ```bash
    ./pipex infile "cmd1" "cmd2" outfile

## Directory structure
    .
    ├── Makefile                # Build and cleaning rules
    ├── includes                # Header files
    │   └── pipex.h             # Main header file
    ├── libft                   # Custom library
    │   ├── Makefile            # Makefile for libft
    │   ├── *.c                 # Various C files for utility functions
    │   ├── ft_printf           # ft_printf implementation
    │   ├── get_next_line       # get_next_line implementation
    │   └── libft.h             # Header file for libft
    ├── pipex_tester            # Tester for Pipex
    ├── src                     # Source files for the core logic
    │   ├── execution.c         # Handles command execution
    │   ├── path_parsing.c      # Resolves the command paths
    │   ├── pipeline            # Pipeline-specific functionalities
    │   │   ├── heredoc.c       # Handles heredoc logic
    │   │   └── pipeline.c      # Sets up and runs the pipeline
    │   ├── pipex               # Main Pipex logic
    │   │   └── pipex.c         # Entry point of the program
    │   └── utils.c             # Utility functions for Pipex
    └── tester_pipex.sh         # Script to test the Pipex program
