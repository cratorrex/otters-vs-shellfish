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

# edge cases
## UNKNOWN COMMAND
> ***fail 127*** `{shell}: {cmd}: command not found`
<hr>

## cd 
cd always fails with 1
<hr>

### `cd a b` `cd a b c` `...`
cd can only accept 0 or 1 arguments  
> ***fail 1*** `{shell}: cd: too many arguments`
<hr/>

### Invalid file or directory `cd {non-existant}`
> ***fail 1*** `{shell}: cd: {arg}: No such file or directory`
<hr/>

### No permission to execute into directory `cd .` `cd {no-X-dir}`
cd needs to be able to execute (`--x`)  
> ***fail 1*** `{shell}: cd: {arg}: Permission denied`
> > this requires only the execute permission so `chmod 111 {dir}` is enough to cd be successful.
>
> `cd .` also requires `--x` to be successful.
<hr/>

### Not a directory `cd {non-directory}`
> ***fail 1*** `{shell}: cd: {arg}: Not a directory`
<hr/>

### `cd -`
Goes to the directory in `$OLDPWD`  
**can also fail as above**  
> ***fail 1*** `{shell}: cd: OLDPWD not set`
<hr/>


## pwd
prints `$PWD` or the result of `getcwd()`  
> following `man 1p pwd`:
> ```
> -L		[...] Otherwise, the -L option shall behave as the -P option.
> 
> 	If the PWD environment variable contains an absolute pathname
> 	of the current directory and the pathname does not contain any
> 	components that are dot or dot-dot, pwd shall write  this
> 	pathname  to  standard  output,  except that if the PWD 
> 	environment variable is longer than {PATH_MAX} bytes including
> 	the terminating null, it is unspecified whether pwd writes this
> 	pathname to standard output or behaves as if the -P option had 
> 	been specified. Otherwise, the -L option shall behave as the -P
> 	option.
pwd should never fail unless `strlen($PATH) >= 4096`, incl the `\0`

## echo
prints {string} to `fd 1`  
this supposedly follows the BSD implementation, incompatible with System V

afaik it's always successful

## export
### `export`
stumbled upon this by random chance...  
but basically...  
it's undefined, but in our bash, it follows similarly to env.
```bash
export {KEY}="{VALUE}"

# as such the following
> export # will output
  export A="B"
  export c="d"
#...
```

### `export {KEY}`
> ***success 0***, does not export the variable unless it has a local value
>>```bash
>> t=12345
>> export t
>> # this is valid in context and it will appear in `env`, as it has a value.
>>```

### `export {KEY}=`
***success 0*** exports the variable as an empty string
```bash
  > export a=
<0>
  > env
<0> [...]
  | a=
  | [...]
```

### `export {inval}...`
export fails if (***fail 1***)

- the first character of {KEY} is not `[A-Z] [a-z] [_]`
> ```bash
> export 1abc=abcdef
> {shell}: export: `{KEY}': not a valid identifier
> ```

- {KEY} contains any non alphanumeric or underscore
> ```bash
> # examples of keys that will fail
> # error is the same 
> abc-123
> %abc
> $
> 123
> ```
<hr/>

### `export {arg1} {arg2} [...]`
***success 0*** all valid are exported  
***fail 1*** all valid are exported, regardless of order


## exit
all statements will print
```bash
exit
|> if error print error 
```

### `exit` `exit {number}`
***success***, return default 0, else any number, mod256

### `exit {non-number}` `exit {random}`
***success, but 2, regardless*** `{shell}: exit: {arg}: numeric argument required`

### `exit {arg1} {arg2} [...]`
***fail 127*** `{shell}: exit: too many arguments`

## unset
### `unset [args ...]`
***success 0***
unsets all valid variables, skips otherwise

***fail >0***
on the extreme off chance that any valid variable cannot be unset...

## env
***success 0***
prints env

***fail 1-125***
something happened that caused the printing to fail...