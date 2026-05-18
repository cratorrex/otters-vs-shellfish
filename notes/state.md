# Overview of structure of project
shell pipeline:  
> see: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation-1  

request input (readline)  

process input
- splitting up "words" and "operators"  
  - what is a "word"?
  - What way do we want to parse?
  - Quotation priority
  - Expansion of aliases `$`
- parse commands
- expand tokens
- perform any redirections  

execute the command  

optionally wait() :face_with_raised_eyebrow: and get exit status


### What is a word?
- > These tokens are separated by metacharacters.  
  - > A metacharacter is a space, tab, newline, or one of: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. 
- Subject only requires handling pairs of closed quotes `" "`/`' '`, redirections `<` `>` `<<` `>>`, pipes `|`, and exit `$?`
  - and for bonus, logic operators AND `&&`, OR `||`, and parentheses `()`, and wildcards `*`


### During Readline

> readline(3)
>> readline()
>>> https://medium.com/@moritz.knoll/learning-valgrind-the-hard-way-creating-suppression-files-that-actually-work-80e246215678

> history(3)  
>> add_history()

> 

prompt while waiting  
```bash
minishell>_
```

working history

keypresses (?)  
- [Signals](https://en.wikipedia.org/wiki/Signal_(IPC))
- tab (i dont think we need this, actually)

- [^C](https://en.wikipedia.org/wiki/Control-C#In_command-line_environments) (SIGINT)

- [^D](https://en.wikipedia.org/wiki/End-of-Transmission_character) (EOT)

- [^\\](https://en.wikipedia.org/wiki/Control-%5C) (SIGQUIT)
  > Under most UNIX-based operating systems control-\ is used to terminate a running process from a command shell and have it produce a memory core dump by sending it a SIGQUIT signal. Other similar ways of terminating or interrupting a shell process include Control-C, Control-Z, and the kill command. 

