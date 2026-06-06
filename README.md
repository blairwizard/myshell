# myshell

A lightweight mini shell written in C that handles everyday terminal commands with a clean colored prompt. Built from scratch using core Linux systems programming concepts like `fork`, `execvp`, and `pipe`.

---

## Build

```bash
gcc shell.c -o myshell
```

## Run

```bash
./myshell
```

To run from anywhere, add the folder to your PATH:

```bash
export PATH=$PATH:/path/to/myshell
```

To make it permanent, add that line to your `~/.bashrc` or `~/.zshrc` and run `source ~/.bashrc`.

---

## Features

### Built-in Commands

| Command       | Description                          |
|---------------|--------------------------------------|
| `cd <dir>`    | Change directory                     |
| `history`     | Show all previously entered commands |
| `help`        | List available commands              |
| `clear`       | Clear the terminal screen            |
| `!!`          | Repeat the last command              |
| `exit`        | Quit the shell                       |

### System Commands
Any standard system command works directly — `ls`, `pwd`, `echo`, `cat`, `mkdir`, and more.

### Piping
Connect commands together using `|`:
```
ls | grep .c
cat file.txt | grep hello
```

### Colored Prompt
Displays your current directory in a colored prompt:
```
myshell:/home/adi/myshell>
```

---

## Examples

```bash
myshell:/home/adi> ls
myshell:/home/adi> cd myshell
myshell:/home/adi/myshell> ls | grep .c
myshell:/home/adi/myshell> history
myshell:/home/adi/myshell> !!
myshell:/home/adi/myshell> clear
myshell:/home/adi/myshell> exit
```

---

## How It Works

- **`fork()`** — creates a child process for each command
- **`execvp()`** — replaces the child with the requested program
- **`wait()`** — parent waits for the child to finish
- **`pipe()`** — connects stdout of one command to stdin of another
- **`dup2()`** — redirects file descriptors for piping
- **`chdir()`** — handles `cd` directly in the parent process

---

## File Structure

```
.
├── shell.c     — All shell logic
└── README.md
```

---

## Known Limitations

- Only single `|` pipe supported (no chaining like `a | b | c`)
- No input/output redirection (`>`, `<`)
- No tab completion
