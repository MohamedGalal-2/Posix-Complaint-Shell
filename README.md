# Posix-Compliant-Shell

This repository contains a POSIX-compliant shell implementation written in C. The shell provides a basic command-line interface for interacting with the operating system.

![Header](https://github.com/MohamedGalal-2/Posix-Complaint-Shell/blob/main/asset.jpg)

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

### Installation
Clone this repository using the following command:

```bash
git clone https://github.com/MohamedGalal-2/Posix-Compliant-Shell.git
```

Navigate to the project directory and compile the source code:

```bash
cd Posix-Compliant-Shell
gcc -o posix_shell main.c shell.c builtIns.c colors.c command_handling.c parser.c
```

### Usage
To start the shell, run the compiled executable:

```bash
./posix_shell
```

You can then enter commands as you would in a standard shell. Type `exit` to quit the shell.

### Features
- Command execution: Executes built-in and external commands.
- Redirection: Supports input and output redirection.
- Piping: Allows command piping.
- Environment variables: Handles environment variables.
- Background execution: Supports running processes in the background.

### Examples
Here are some example commands you can try in the shell:

```sh
# Running a simple command
ls -l

# Using input and output redirection
cat < input.txt > output.txt

# Piping commands
ls -l | grep ".c"

# Setting and using environment variables
export MY_VAR="Hello"
echo $MY_VAR

# Running a command in the background
sleep 60 &
```

### Contributing
Contributions are welcome! Please fork this repository, make your changes, and submit a pull request.

### License
This repository is licensed under the MIT License. See the [LICENSE](./LICENSE) file for more details.
