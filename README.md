<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>minishell
</h1>
<h3>◦ Think small, shell big!</h3>
<h3>◦ Developed with the software and tools listed below.</h3>

<p align="center">
<img src="https://img.shields.io/badge/C-A8B9CC.svg?style&logo=C&logoColor=black" alt="C" />
<img src="https://img.shields.io/badge/Markdown-000000.svg?style&logo=Markdown&logoColor=white" alt="Markdown" />
</p>
<img src="https://img.shields.io/github/languages/top/zneel/minishell?style&color=5D6D7E" alt="GitHub top language" />
<img src="https://img.shields.io/github/languages/code-size/zneel/minishell?style&color=5D6D7E" alt="GitHub code size in bytes" />
<img src="https://img.shields.io/github/commit-activity/m/zneel/minishell?style&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/license/zneel/minishell?style&color=5D6D7E" alt="GitHub license" />
</div>

---

## 📒 Table of Contents
- [📒 Table of Contents](#-table-of-contents)
- [📍 Overview](#-overview)
- [⚙️ Features](#-features)
- [📂 Project Structure](#project-structure)
- [🧩 Modules](#modules)
- [🚀 Getting Started](#-getting-started)
- [🗺 Roadmap](#-roadmap)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👏 Acknowledgments](#-acknowledgments)

---


## 📍 Overview

HTTPStatus Exception: 400

---

## ⚙️ Features

HTTPStatus Exception: 400

---


## 📂 Project Structure




---

## 🧩 Modules

<details closed><summary>Root</summary>

| File                                                              | Summary                                                                                                                                                                                                                                                                                                               |
| ---                                                               | ---                                                                                                                                                                                                                                                                                                                   |
| [Makefile](https://github.com/zneel/minishell/blob/main/Makefile) | The code is for a minishell program and includes functionalities such as prompt generation, tokenizing and parsing input, handling built-in commands, environment variables, and executing commands with pipes and file redirection. It also provides error handling and supports debugging and sanitization options. |

</details>

<details closed><summary>Src</summary>

| File                                                                    | Summary                                                                                                                                                                                                                                                  |
| ---                                                                     | ---                                                                                                                                                                                                                                                      |
| [shlevel.c](https://github.com/zneel/minishell/blob/main/src/shlevel.c) | The code sets the value of the "SHLVL" environmental variable in a shell program by incrementing the current value or setting it to 1 if it does not exist. This ensures that each new shell instance has a unique value for "SHLVL".                    |
| [utils.c](https://github.com/zneel/minishell/blob/main/src/utils.c)     | This code defines several utility functions for the minishell program. The functions include initializing the minishell, checking if a string consists only of whitespace, duplicating the minishell structure, and closing duplicated file descriptors. |
| [prompt.c](https://github.com/zneel/minishell/blob/main/src/prompt.c)   | The code provides a prompt function that reads input from the user. It handles signals, sets up a readline prompt when running interactively, or uses get_next_line for non-interactive input. The function returns the user's input as a string.        |
| [main.c](https://github.com/zneel/minishell/blob/main/src/main.c)       | The code is a basic implementation of a minishell program. It creates a prompt, reads user input, lexes and parses the input, prepares and executes the commands, and repeats the process until the user exits.                                          |

</details>

<details closed><summary>Builtin</summary>

| File                                                                                        | Summary                                                                                                                                                                                                                                                                                                                                                       |
| ---                                                                                         | ---                                                                                                                                                                                                                                                                                                                                                           |
| [echo.c](https://github.com/zneel/minishell/blob/main/src/builtin/echo.c)                   | The code implements the "echo" command, which prints arguments to the console. It recognizes the "-n" flag and ignores the trailing newline character. The "is_n" function checks if an argument is the "-n" flag. The "echo" function processes arguments and prints them, adding spaces between them, and an optional newline character at the end.         |
| [print_env.c](https://github.com/zneel/minishell/blob/main/src/builtin/print_env.c)         | The core functionality of this code is to print the environment variables stored in a linked list structure. It iterates through the list and displays the key-value pairs, excluding empty values. The function returns 0.                                                                                                                                   |
| [exit.c](https://github.com/zneel/minishell/blob/main/src/builtin/exit.c)                   | The "exit" code provides the functionality to exit the program. It includes functions to convert a string to a long long integer, check for numeric overflow, handle different argument scenarios, and free memory before exiting.                                                                                                                            |
| [export_2.c](https://github.com/zneel/minishell/blob/main/src/builtin/export_2.c)           | The code is a part of a shell implementation and defines two functions:-"replace_env" replaces the value of an environment variable with a new value.-"export_no_value" handles exporting environment variables without specifying a value by adding them to the environment or updating their values if already present.                                     |
| [unset.c](https://github.com/zneel/minishell/blob/main/src/builtin/unset.c)                 | The code defines a function called `unset` that removes environment variables from a linked list `env`. It iterates over the input command and deletes nodes in the list that match the variables to be unset.                                                                                                                                                |
| [export.c](https://github.com/zneel/minishell/blob/main/src/builtin/export.c)               | The code provides functionalities for exporting and managing environment variables in a shell program. It includes functions to validate variable names, create and update environment variables, and print or modify the exported variables.                                                                                                                 |
| [exec_builtin.c](https://github.com/zneel/minishell/blob/main/src/builtin/exec_builtin.c)   | This code implements the execution of built-in commands in a shell. It checks the command type and calls the corresponding function to handle the command, such as cd, unset, echo, etc. It also handles input and output redirection.                                                                                                                        |
| [check_builtin.c](https://github.com/zneel/minishell/blob/main/src/builtin/check_builtin.c) | This code implements a function to check if a command is a built-in command and returns the type of the built-in command. It compares the command with various built-in commands such as echo, export, env, pwd, unset, cd, and exit, and returns the appropriate type if it matches any of them. If it doesn't match any built-in commands, it returns NONE. |
| [pwd.c](https://github.com/zneel/minishell/blob/main/src/builtin/pwd.c)                     | The code is a function for printing the current working directory (PWD) in a shell. It checks the environment variables, specifically the PWD variable, and if found, prints the value. Otherwise, it calls the getcwd() function to get the current directory and prints it.                                                                                 |
| [cd.c](https://github.com/zneel/minishell/blob/main/src/builtin/cd.c)                       | The code defines the functionalities of the "cd" command in a Unix-based shell. It allows the user to change the current working directory to a specified path, the home directory, or the previous directory. It also handles error messages for invalid paths and permission issues.                                                                        |
| [builtin_utils.c](https://github.com/zneel/minishell/blob/main/src/builtin/builtin_utils.c) | The code is a part of a set of built-in functions in a larger program. It contains the'arg_len' function which calculates the length of an array of strings. It counts and returns the number of elements in the array.                                                                                                                                       |

</details>

<details closed><summary>Expand</summary>

| File                                                                               | Summary                                                                                                                                                                                                                                                                                                                                                                                      |
| ---                                                                                | ---                                                                                                                                                                                                                                                                                                                                                                                          |
| [utils.c](https://github.com/zneel/minishell/blob/main/src/expand/utils.c)         | The code provides a set of utility functions for the expand module. It includes functions for freeing expand variables, copying and incrementing strings, changing the state of the expand object, freeing redirections, and deleting expand nodes from a linked list.                                                                                                                       |
| [variables.c](https://github.com/zneel/minishell/blob/main/src/expand/variables.c) | The code handles variable expansion in a shell program. It identifies variables preceded by a dollar sign ($) and replaces them with their corresponding values from the environment. It also handles special cases like the last exit status and escaped dollar signs.                                                                                                                      |
| [expand.c](https://github.com/zneel/minishell/blob/main/src/expand/expand.c)       | The "expand.c" code file defines functions for expanding variables, quotes, and dollar signs in a given input string. It handles single and double quotes, dollar signs followed by variable names, and expands them accordingly. It also allocates memory for the expanded result and cleans up any unused memory. There are separate functions for expanding arguments and redirect files. |

</details>

<details closed><summary>Signals</summary>

| File                                                                            | Summary                                                                                                                                                                                                                                                                                            |
| ---                                                                             | ---                                                                                                                                                                                                                                                                                                |
| [signals.c](https://github.com/zneel/minishell/blob/main/src/signals/signals.c) | This code handles signals in a minishell program. It includes signal handlers for SIGINT and SIGQUIT, as well as a handler for a here document signal. When SIGINT is received, the code performs specific actions depending on the context. When SIGQUIT is received, it clears the current line. |

</details>

<details closed><summary>Env</summary>

| File                                                                                              | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| ---                                                                                               | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| [ft_lstsort_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstsort_env.c)         | This code defines a function that sorts a linked list of key-value pairs in alphabetical order based on the key. It uses the bubble sort algorithm to compare and swap the elements until the list is sorted.                                                                                                                                                                                                                                                                                                                                                                                              |
| [ft_lstadd_back_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstadd_back_env.c) | The code defines a function, ft_lstadd_back_env, that adds a new node to the end of a linked list. If the list is empty, the new node becomes the head of the list. Otherwise, it iterates through the list until finding the last node and sets the next pointer of that last node to the new node.                                                                                                                                                                                                                                                                                                       |
| [get_env.c](https://github.com/zneel/minishell/blob/main/src/env/get_env.c)                       | The get_env function retrieves the corresponding value from a key-value pair in the minishell environment. It compares the provided key to those in the environment and returns the value if a match is found, or NULL otherwise.                                                                                                                                                                                                                                                                                                                                                                          |
| [env_cpy.c](https://github.com/zneel/minishell/blob/main/src/env/env_cpy.c)                       | The code defines two functions-ft_separate() to split a string and ft_lstcpy_env() to copy environment variables into a linked list. The ft_separate() function takes a string and a separator character as inputs, splits the string at the separator, and returns an array of two strings. The ft_lstcpy_env() function takes an array of strings representing environment variables, calls ft_separate() to split each string into key-value pairs, creates a new node for each pair, and adds the node to the linked list. The resulting linked list containing the environment variables is returned. |
| [ft_lstclear_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstclear_env.c)       | The ft_lstclear_env function is responsible for clearing a linked list containing key-value pairs. It takes a double pointer to the linked list and a function pointer to a delete function. The function iterates through the list, deleting the key and value for each node, freeing the memory, and setting the list pointer to NULL.                                                                                                                                                                                                                                                                   |
| [convert_env.c](https://github.com/zneel/minishell/blob/main/src/env/convert_env.c)               | The code `convert_env.c` defines a function `convert_env` that converts a linked list of key-value pairs into a two-dimensional array. Each element in the array represents an environment variable in the form of "key=value". The function handles memory allocation and returns the resulting array.                                                                                                                                                                                                                                                                                                    |
| [ft_lstsize_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstsize_env.c)         | The code implements a function `ft_lstsize_env` that counts the number of elements in a linked list named `lst`. It iterates through the list and increments a counter `size` for each element. The function returns the final count of elements in the list.                                                                                                                                                                                                                                                                                                                                              |
| [modif_env.c](https://github.com/zneel/minishell/blob/main/src/env/modif_env.c)                   | The code defines a function "modif_env" that modifies the value of a key in a linked list of key-value pairs representing environment variables. It takes in the minishell structure, the key, and the new value. It searches for the key in the linked list and updates its value with the new value. If the value update is successful, it returns 0; otherwise, it returns 1.                                                                                                                                                                                                                           |
| [ft_lstcpy_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstcpy_env.c)           | The function `ft_lstcpy_env` is used to create a copy of a linked list containing key-value pairs. It takes the top of the original list as input and returns a new list with the same content. The function ensures that memory is allocated correctly for the copied elements.                                                                                                                                                                                                                                                                                                                           |
| [ft_lstnew_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstnew_env.c)           | The code defines a function ft_lstnew_env that creates a new node for a linked list to store key-value pairs. It takes two parameters, key and value, and returns a pointer to the newly created node. The node contains the key, value, and a pointer to the next node in the list.                                                                                                                                                                                                                                                                                                                       |
| [free_mat.c](https://github.com/zneel/minishell/blob/main/src/env/free_mat.c)                     | The code provides a function called free_mat that deallocates memory for a dynamic 2D array of strings.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| [ft_lstdelone_env.c](https://github.com/zneel/minishell/blob/main/src/env/ft_lstdelone_env.c)     | The code defines a function "ft_lstdelone_env" that takes a linked list node of type "t_kv" and a function pointer to delete its key and value. It frees the node after deleting its content, only if the node and the delete function exist.                                                                                                                                                                                                                                                                                                                                                              |

</details>

<details closed><summary>Parser</summary>

| File                                                                           | Summary                                                                                                                                                                                                                                                                                                                                                                                |
| ---                                                                            | ---                                                                                                                                                                                                                                                                                                                                                                                    |
| [grammar.c](https://github.com/zneel/minishell/blob/main/src/parser/grammar.c) | The code contains functions for parsing and building an abstract syntax tree (AST) for a shell script. It includes functions for parsing pipeline commands, logical expressions, and command lines. The code checks for syntax errors and returns the root of the AST.                                                                                                                 |
| [parser.c](https://github.com/zneel/minishell/blob/main/src/parser/parser.c)   | The code is responsible for parsing input commands in a minishell. It initializes a parser, reads tokens from a lexer, and applies a grammar to construct a parse tree. The resulting parse tree represents the structure of the command.                                                                                                                                              |
| [io.c](https://github.com/zneel/minishell/blob/main/src/parser/io.c)           | The code implements the functions for parsing and handling input/output redirection in a shell program. It checks for redirect symbols, accepts them, and retrieves the corresponding file name to associate with the command.                                                                                                                                                         |
| [group.c](https://github.com/zneel/minishell/blob/main/src/parser/group.c)     | The code defines a function called "group" that takes in a parser object. It calls another function called "command_line" to parse a command line and store the result in a "node" variable. If the node is valid, it checks if there is a closing parenthesis. If there is, it removes the node from the parse stack and returns it. Otherwise, it deletes the node and returns NULL. |
| [utils.c](https://github.com/zneel/minishell/blob/main/src/parser/utils.c)     | The code defines a function to convert a token type from the lexer into a corresponding node type for the parser. The node types represent different elements of a shell command, such as input/output redirection, piping, and commands themselves.                                                                                                                                   |
| [actions.c](https://github.com/zneel/minishell/blob/main/src/parser/actions.c) | The code provides functions for accepting, peeking, and expecting specific types of tokens in a parser structure. It allows the parser to check if the current token matches a desired type, advance to the next token, and perform similar operations with future tokens.                                                                                                             |
| [command.c](https://github.com/zneel/minishell/blob/main/src/parser/command.c) | The code defines functions for parsing commands in a shell-like language. It checks for redirect tokens and counts arguments. It creates a command node and adds arguments and input/output redirections to it. The functions are used to build an Abstract Syntax Tree (AST) for further processing.                                                                                  |
| [ast.c](https://github.com/zneel/minishell/blob/main/src/parser/ast.c)         | This code implements a basic abstract syntax tree (AST) for a command line interpreter. It includes functions to create new nodes, attach child nodes to parent nodes, delete nodes and their associated data (arguments and redirections).                                                                                                                                            |

</details>

<details closed><summary>Exec</summary>

| File                                                                                     | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| ---                                                                                      | ---                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| [exec_mini.c](https://github.com/zneel/minishell/blob/main/src/exec/exec_mini.c)         | The code provides the main execution functionality for a mini shell program. It includes functions for executing commands, built-in functions, and handling logical operators like &&, ||, and pipes. The code creates processes, executes commands, and waits for them to finish. It also handles error cases and manages the shell's environment.                                                                                             |
| [path.c](https://github.com/zneel/minishell/blob/main/src/exec/path.c)                   | This code implements a functionality to find the executable path for a given command by searching through the directories included in the PATH environment variable. It checks if the given command is a valid executable by using the access function. It then splits the PATH variable into individual directories and appends the command to each directory to find the full path. If a valid executable is found, it returns the full path. |
| [here_doc.c](https://github.com/zneel/minishell/blob/main/src/exec/here_doc.c)           | The code implements the functionality for inputting text until a specified delimiter is encountered.It compares the input with the delimiter, writes the input to a file, and repeats until the delimiter is found.                                                                                                                                                                                                                             |
| [dup.c](https://github.com/zneel/minishell/blob/main/src/exec/dup.c)                     | The code provides functions for duplicating file descriptors: dup_out duplicates STDOUT_FILENO, and dup_in duplicates STDIN_FILENO. These functions handle different file opening scenarios and error handling.                                                                                                                                                                                                                                 |
| [init_command.c](https://github.com/zneel/minishell/blob/main/src/exec/init_command.c)   | The code includes functions to initialize a command structure, open files for redirection, and convert a node into a command.                                                                                                                                                                                                                                                                                                                   |
| [middle_pipe.c](https://github.com/zneel/minishell/blob/main/src/exec/middle_pipe.c)     | The code implements a function that executes a command with input and output redirection using pipes. It forks a child process, sets up the necessary pipe connections, and redirects the input and output accordingly. The child process then executes the command using the execve system call. The function returns 0 if successful.                                                                                                         |
| [pipe_utils.c](https://github.com/zneel/minishell/blob/main/src/exec/pipe_utils.c)       | The code contains a function to handle built-in commands in a shell, a function to close pipes and free memory, and a helper function to close pipe file descriptors.                                                                                                                                                                                                                                                                           |
| [exec.c](https://github.com/zneel/minishell/blob/main/src/exec/exec.c)                   | The "exec.c" file contains functions for executing commands in the minishell program. The code handles different types of commands, such as pipes, logical operators (OR and AND), and regular commands. It also includes functions for managing child processes and handling signals. Overall, the code provides the core functionality for executing commands in the minishell program.                                                       |
| [convert_arg.c](https://github.com/zneel/minishell/blob/main/src/exec/convert_arg.c)     | The "convert_arg" function takes a linked list as input and converts it into a null-terminated array of strings. It allocates memory for the array and each string, then copies the content of each node in the linked list into the corresponding string in the array. Finally, it sets the last element of the array to NULL before returning it.                                                                                             |
| [error.c](https://github.com/zneel/minishell/blob/main/src/exec/error.c)                 | The code provides functions for handling errors in a minishell program. It includes functions for freeing memory, displaying error messages, and handling execution failures.                                                                                                                                                                                                                                                                   |
| [open_file_cmd.c](https://github.com/zneel/minishell/blob/main/src/exec/open_file_cmd.c) | This code implements functions to handle input and output file redirection for a shell command execution. It checks the access permissions and existence of input and output files, and sets appropriate flags and file paths in the command structure.                                                                                                                                                                                         |
| [last_pipe.c](https://github.com/zneel/minishell/blob/main/src/exec/last_pipe.c)         | This code defines the core functionalities for executing the last command in a shell pipeline. It handles the child and parent processes, redirects input and output, checks for built-in commands, and executes the command using `execve`.                                                                                                                                                                                                    |
| [cmd.c](https://github.com/zneel/minishell/blob/main/src/exec/cmd.c)                     | The code defines functions for executing a command in a minishell environment. It sets up the appropriate environment variables, redirects input and output if necessary, forks a child process to execute the command, and handles any execution failures.                                                                                                                                                                                     |
| [utils.c](https://github.com/zneel/minishell/blob/main/src/exec/utils.c)                 | The code defines utility functions for initializing pipes, a function that does nothing, and a function that checks if two strings are the same.                                                                                                                                                                                                                                                                                                |
| [first_pipe.c](https://github.com/zneel/minishell/blob/main/src/exec/first_pipe.c)       | The code features a function called `execute_first` that creates a pipe, forks a child process, and executes a command based on the given input. The parent process handles the pipes and the child process sets up the necessary input/output redirections. The command can be a built-in function or an external program.                                                                                                                     |
| [pipeline.c](https://github.com/zneel/minishell/blob/main/src/exec/pipeline.c)           | This code implements the execution of a pipeline in a minishell. It recursively processes the nodes in the pipeline and executes the commands using pipes for inter-process communication.                                                                                                                                                                                                                                                      |

</details>

<details closed><summary>Lexer</summary>

| File                                                                          | Summary                                                                                                                                                                                                                                                                                                                                                                                                                              |
| ---                                                                           | ---                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| [lexer.c](https://github.com/zneel/minishell/blob/main/src/lexer/lexer.c)     | The code is a lexer implementation that tokenizes input strings. It initializes a lexer struct, peeks at the next character, advances the lexer position, advances twice, and tokenizes the input string. The lexer handles whitespace characters, adds tokens, and eventually returns the lexer struct.                                                                                                                             |
| [checker.c](https://github.com/zneel/minishell/blob/main/src/lexer/checker.c) | The code contains functions to check if quotes in a given line are valid. It uses a stack data structure to keep track of the opening and closing quotes. If any unclosed quotes are found, an error message is displayed. The "validate" function checks if the provided lexer object and line are valid, and then calls the "quotes_valid" function to validate the quotes. The code ensures correct quotes usage in a given line. |
| [token.c](https://github.com/zneel/minishell/blob/main/src/lexer/token.c)     | The code provides the core functionalities for handling tokens in a lexer. It includes functions for creating new tokens with a specified type and value, retrieving the next token from the lexer, and adding the token to the token list. The code also handles specific token types such as OR, AND, PIPE, LPAREN, RPAREN, DGREAT, DLESS, GREAT, LESS, and WORD.                                                                  |
| [words.c](https://github.com/zneel/minishell/blob/main/src/lexer/words.c)     | This code defines functions for identifying special characters, escaping quotes, and handling words in a lexer program. It is used to tokenize input strings for further processing.                                                                                                                                                                                                                                                 |
| [debug.c](https://github.com/zneel/minishell/blob/main/src/lexer/debug.c)     | The code defines a function to convert a token type into a corresponding string representation. It handles various token types like words, pipes, logical operators, redirection operators, parentheses, and others.                                                                                                                                                                                                                 |
| [delete.c](https://github.com/zneel/minishell/blob/main/src/lexer/delete.c)   | This code defines functions to delete tokens and a lexer structure. It frees the memory allocated for the tokens and the lexer.                                                                                                                                                                                                                                                                                                      |

</details>

<details closed><summary>Include</summary>

| File                                                                            | Summary                                                                                                                                                                                                                                                                                                                                                                                                                       |
| ---                                                                             | ---                                                                                                                                                                                                                                                                                                                                                                                                                           |
| [minishell.h](https://github.com/zneel/minishell/blob/main/include/minishell.h) | The `minishell.h` header file provides the necessary function prototypes, definitions, and data structures for a mini shell program. It includes libraries such as `libft.h`, `fcntl.h`, and `signal.h`, and defines various enums and structs for command configuration. Additionally, it declares functions for manipulating environment variables, copying variables, modifying variables, and initializing the minishell. |
| [structs.h](https://github.com/zneel/minishell/blob/main/include/structs.h)     | The code defines various data structures for implementing a shell program. It includes structures for tokens, lexer state, parser state, command nodes, redirects, and the overall shell state.                                                                                                                                                                                                                               |
| [signals.h](https://github.com/zneel/minishell/blob/main/include/signals.h)     | The code in the "signals.h" file defines functions for handling various signals in a minishell program. It includes functionality for handling SIGINT, SIGTERM, and SIGQUIT signals, as well as setting up the signal handlers. The "g_sigint" variable is used to handle the SIGINT signal.                                                                                                                                  |
| [exec.h](https://github.com/zneel/minishell/blob/main/include/exec.h)           | The code includes various functions for executing commands in a minishell program. It handles parsing, executing built-in commands and external commands, as well as executing commands with pipes, redirects and here documents. It also includes helper functions for managing file descriptors and pipes.                                                                                                                  |
| [builtin.h](https://github.com/zneel/minishell/blob/main/include/builtin.h)     | The "builtin.h" file contains definitions and declarations for built-in commands in a shell program. It includes functions for executing commands such as echo, export, env, pwd, unset, cd, exit, and W_PATH. These functions provide functionalities like printing messages, manipulating environment variables, changing directories, and exiting the shell.                                                               |
| [lexer.h](https://github.com/zneel/minishell/blob/main/include/lexer.h)         | This code provides the functionalities for a lexer, including creating, deleting, and advancing tokens, as well as handling special characters and validating the lexer. It also has functions for debugging and converting tokens to strings.                                                                                                                                                                                |
| [expand.h](https://github.com/zneel/minishell/blob/main/include/expand.h)       | The code defines a set of functions and structures for expanding variables and quotes in a shell. It includes functions for expanding arguments and redirects, as well as handling special characters like dollar signs. It also provides helper functions for manipulating strings and managing state.                                                                                                                       |
| [parser.h](https://github.com/zneel/minishell/blob/main/include/parser.h)       | This code defines a set of functions and structures for parsing and processing a grammar. It includes functions for accepting, expecting, and peeking at token types, as well as functions for parsing different grammatical elements. It also includes functions for creating and manipulating an abstract syntax tree (AST) and utility functions for printing the AST and converting token types.                          |

</details>

---

## 🚀 Getting Started

### ✔️ Prerequisites

Before you begin, ensure that you have the following prerequisites installed:
> - `ℹ️ Requirement 1`
> - `ℹ️ Requirement 2`
> - `ℹ️ ...`

### 📦 Installation

1. Clone the minishell repository:
```sh
git clone https://github.com/zneel/minishell
```

2. Change to the project directory:
```sh
cd minishell
```

3. Install the dependencies:
```sh
gcc -o myapp main.c
```

### 🎮 Using minishell

```sh
./myapp
```

### 🧪 Running Tests
```sh
/* No common unit test framework in C */
```

---


## 🗺 Roadmap

> - [X] `ℹ️  Task 1: Implement X`
> - [ ] `ℹ️  Task 2: Refactor Y`
> - [ ] `ℹ️ ...`


---

## 🤝 Contributing

Contributions are always welcome! Please follow these steps:
1. Fork the project repository. This creates a copy of the project on your account that you can modify without affecting the original project.
2. Clone the forked repository to your local machine using a Git client like Git or GitHub Desktop.
3. Create a new branch with a descriptive name (e.g., `new-feature-branch` or `bugfix-issue-123`).
```sh
git checkout -b new-feature-branch
```
4. Make changes to the project's codebase.
5. Commit your changes to your local branch with a clear commit message that explains the changes you've made.
```sh
git commit -m 'Implemented new feature.'
```
6. Push your changes to your forked repository on GitHub using the following command
```sh
git push origin new-feature-branch
```
7. Create a new pull request to the original project repository. In the pull request, describe the changes you've made and why they're necessary.
The project maintainers will review your changes and provide feedback or merge them into the main branch.

---

## 📄 License

This project is licensed under the `ℹ️  INSERT-LICENSE-TYPE` License. See the [LICENSE](https://docs.github.com/en/communities/setting-up-your-project-for-healthy-contributions/adding-a-license-to-a-repository) file for additional info.

---

## 👏 Acknowledgments

> - `ℹ️  List any resources, contributors, inspiration, etc.`

---
