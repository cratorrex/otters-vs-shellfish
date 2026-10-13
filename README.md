*This project has been created as part of the 42 curriculum by thtay and jatansil*.

# Description
### minishell - As beautiful as a shell
Typing commands into a terminal interface is a thing that existed ever since the dawn of computers, a shell as it's called. This project tasks a group of 2 people to work together in order to recreate/mimic Bash - Bourne Again SHell.

> Bash is the shell, or command language interpreter, for the GNU operating system. [...] A shell is simply a macro processor that executes commands. - Bash manual

How it works is that it takes a "statement" read by the terminal, breaks it into tokens, parses the tokens, and executes a command statement that is the interpretation of those tokens.

A simple example would be as follows:  
```bash
echo hello world
# the expected output would be the words "hello world", followed by a new line.
# in this case, echo is the command, whose job is to print out words, followed by a new line.
```
We'll explore more of this through the following subsections.

## Process

### Readline - Reading Input
Readline is one of the libraries we're supposed to use for this project. What it does in essence is it takes a line that has been typed, delimited by the `\n` newline character, and sends the read line to be processed.

Readline produces memory leaks, but the subject defines that we do not need to worry about those. Hence we will have to also add in our own suppression file(s) to ignore these leaks in our code execution.

Readline returns a malloced string denoting the line that has been read by the standard input. This line has to be eventually freed.

If the line is empty or delimited strictly by whitespace (spaces and tabs), nothing is done and a new line is prompted.

### Tokens
Tokens are basically what's considered by the shell as parts of an instruction or command. Delimited by trailing whitespace, the shell reads through the line, and classifies all the "tokens" it encounters. The process repeats until the entire line has been tokenized.

#### Operators - Redirections and Pipes
Our tokenizer recognises redirections and pipes as "operators". Operators will lead into different results of execution, like taking input from a different file, sending to a new command process, outputting to a file, and a bit more. If the token is not an operator, it's treated as a "word".

### Parser
Before the tokens are passed into the parser, some syntax will need to be validated, like unclosed quotes, and incomplete commands like unfinished pipes and the like.

But anyways, now the tokens are passed into the parser to create the command syntax. If it is a word, it's added to the command's vectors, else it's sent to the redirections list. The order of the redirections matter, as we'll see later. We continue until all tokens have been parsed.  
If a command has pipes, a new command will be created, thusly named a pipeline.

### Expansion
The parsed command thus far may still have things that need to be processed, like environment variables and the like. These vectors will undergo expansion, in which their keys are substituted for values, in which the execution module will use.

This expansion also has states. If it is unquoted, in single or double quotes. Only one quote state can be active at a time, so `'"'` will not toggle the Double quote state while in the Single quotes.

Special characters are usually identified here and expanded accordingly.  
- `~` Tilde
> An unquoted tilde (or tilde that is not in contact with a quote) will be expanded into the user's HOME Directory. 
- `$` Dollar
> Dollar signs are special characters as they usually denote a variable, of name based on the text next to the dollar sign, until it encounters another special character. This does not happen if the sign is enclosed in Single Quotes `' '`.

### Redirections
Before the command is execute though, there is some thing to do with the redirections. This is where it happens.

Redirections are processed from left to right, based on the redirection type, Left or Right (< OR >).

#### Left Redirections (`<` and `<<`)
Left redirections take input from either a file or a stream of delimited input.  
For the single left `<` redirection, the "target" file is specified and attempted to be opened. This will error if the file does not exist or the read permission is not allowed.  
Whether or not it is successful, it will carry on to the next left redirection, but will track the first error redirection.

The double left `<<` redirection is also known as a here-document. This takes the specified "target" as a End of File delimiter, rather than a file to be opened. This takes from the standard input (fd 0) and continuously collects line after line until it receives a line that contains the aforementioned target delimiter, at which point it stops the here-document and continues to the next left redirection if any.  
Every subsequent left redirection should close the previous left redirection's file descriptor before opening another file descriptor, so no "progress" is carried over to the next redirection.

After this process ends, if there is an error, it stops here and doesn't continue. But if there is no errors, it continues on to the right redirections.

#### Right Redirections (`>` and `>>`)
Right redirections are much less complicated. They change the output "target" of a command to a designated file of choice.  
This opens the file in it's current state and attempts to `>` overwrite, or `>>` append to it. If the file's permissions are denied to write, an error will be returned, and the process stops there and does not continue to the next right redirection.

### Execution
There's a few cases in which execution takes place.  
Builtins, non-builtins, and pipelines.

#### Builtins
Builtins are basically commands that are baked into the shell, used to do essential stuff that makes the shell function. Stuff like `cd`, the change directory command.  
These commands by themselves do not create new processes, and stay native to the current shell process. The exit status is collected at the end of execution.

#### Non-Builtins
Non-builtins are commands that are linked to executable binaries usually installed into the operating system. They can also be launchable programs like bash and minishell. Commands are passed into `execve()` through a forked process, so there is some clean up to do, since a forked process duplicates all the resources in use of the parent process, including all allocated memory.  
The exit status is collected once the program ends it's execution.

#### Pipelines
Pipelines are a chain of commands, builtins or not, that pass their outputs, as inputs, into the subesquent commands in the list of commands. This implementation is the same as how we implemented non-builtins due to forked processes. These commands are each sent into forked processes and collected thereafter to be processed again.
The exit status is only collected from the last command executed in the pipeline, regardless of if there are any preceeding errors, assuming the command gets to this stage of the process.

## Builtins
### cd
Changes the current working directory of the shell.  
This also sets the `$PWD` and `$OLDPWD` environment variables accordingly.  
Also accepts the `~` and `-` characters as arguments.
### pwd
Prints the shell's current working directory's physical location. (see considerations)

### echo
Prints out the arguments passed in, to the standard output (`STDOUT` / `fd1`), followed by a new line (`\n`).  
If the `-n` option is specified, it does not append the newline character to the end of the line.

### env
Prints out the list of environment variables that have been exported into the environment.

### export
Attempts to export the given arguments as variables into the environment.  
It will go through all arguments, and export those variables that are valid, and have been declared a value. Any errors encountered will return an exit status of `1`.  
If no argument is specified, the manual defines it as undefined behaviour, subject to implementation.
### unset
Attempts to remove the given arguments as variables from the environment.
It will go through all arguments, and unset those variables that have an environment value. Invalid arguments are ignored, and no error is returned.

### exit
Exits the shell with the given numeric argument as the exit status, defaulting to 0 if no number is given.
Giving 2 or more arguments will not exit the shell and will instead return an error.


## Considerations and Edge Cases

### `~` Tilde
This relies on the HOME environment variable. Since the scope of the subject does not dictate we need to keep inherent track of the user.

### Environment Variables
Variables are unable to be declared locally. The program only keeps track of the variables that have been exported out into the environment, with a value of some kind, through the `export` built-in.

### Redirections
We only handled for absolute or relative file redirections. As such, the following redirection symbols/patterns are not implemented in the solution.
> `<>`, `&>word`, `-`, `>|`, `>&digit`, `>&word`.  
> Basically, we only implemented for the base case `>word`.

### pwd
The subject states to implement the command without options or arguments. The pwd command in bash offers two options, in which it would default to one of the options. We decided to implement this as directly printing out the physical link of the current working directory (the `-P` option).

# Instructions
Clone the repository to your directory of choice and run the `make` command.  
> makefile: `all` `clean` `fclean` `re`

This compiles all sources in the repository into a `./minishell` executable file.  
Run minishell by simply typing:
```bash
./minishell
```

This implementation is intended to mimic the Bash shell, but using the POSIX standard.  
So when comparing results, it's best to launch bash in posix mode:
```bash
bash --posix
```

# Resources
AI prompting in DuckAI and ChatGPT, to understand concepts and the suggested workflow.

https://www.gnu.org/software/bash/manual/bash.html

https://www.man7.org/linux/man-pages/

https://en.wikipedia.org/wiki/Bash_(Unix_shell)