*This project has been created as part of the 42 curriculum by thtay and jatansil*.

# Description
### minishell - As beautiful as a shell
Typing commands into a terminal interface is a thing that existed ever since the dawn of computers, a shell as it's called. This project tasks a group of 2 people to work together in order to recreate Bash - Bourne Again SHell.

> Bash is the shell, or command language interpreter, for the GNU operating system. [...] A shell is simply a macro processor that executes commands. - Bash manual

How it works is that it takes a "statement" read by the terminal, breaks it into tokens, parses the tokens, and executes a command statement that is the interpretation of those tokens.

A simple example would be as follows:  
```bash
echo hello world
# the expected output would be the words "hello world", followed by a new line.
# in this case, echo is the command, whose job is to print out words, followed by a new line.
```

### Tokens
Tokens are basically what's considered by the shell as parts of an instruction or command. Delimited by trailing whitespace (tabs or space characters), the shell reads through the line 

### Parser

### Execution



## Considerations
### pwd
The subject states to implement the command without options or arguments. The pwd command in bash offers two options, in which it would default to one of the options. We decided to interpret this as defaulting to resolving the symbolic link (the -P option).

# Instructions

# Resources
AI prompting in DuckAI and ChatGPT, to understand concepts and the suggested workflow.

https://www.gnu.org/software/bash/manual/bash.html

https://www.man7.org/linux/man-pages/

https://en.wikipedia.org/wiki/Bash_(Unix_shell)