# 42_minishell

# <div align="center">⚙️ minishell (a [42](https://42perpignan.fr/) project) ⚙️</div>

## Grade
![drenassi's 42 minishell Score](https://badge42.coday.fr/api/v2/clph33bao098101t6vnzqbe17/project/3440940)

## Introduction
This project consists in **reproducing the behaviour of bash**. We had to make a *mini bash*.
It had to be coded in **C language**, with a makefile compiling all the files together.
For this project, we had to work in team with another student. It taught us how to work together on the same github repository and on the same project. Each of us made his part to complete the other's part.

This project was done during 42 cursus at 42 Perpignan in January of 2024 with bonus.

## Rules
### General rules
The minishell should:
- Display a **prompt** when waiting for a new command.
- Have a **working history**.
- **Search and launch the right executable** (based on the PATH variable or using a relative or an absolute path).
- Avoid using more than one global variable to indicate a received signal.
- Not interpret unclosed quotes or special characters which are not required by the
subject such as \\ (backslash) or ; (semicolon).
- Handle ’ (**single quote**) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (**double quote**) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement **redirections** : **\<** should redirect input; **\>** should redirect output; **\<\<** should be given a delimiter, then read the input until a line containing the delimiter is seen; **\>\>** should redirect output in append mode.
- Implement **pipes** (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Handle **environment variables** ($ followed by a sequence of characters) which
should expand to their values.
- Handle **$?** which should expand to the exit status of the most recently executed
foreground pipeline.
- Handle **ctrl-C**: it displays a new prompt on a new line.
- Handle **ctrl-D**: it exits the shell.
- Handle **ctrl-\\**: it should do nothing.

### Builtins
Your shell must implement the following builtins:
- **echo** with option -n.
- **cd** with only a relative or absolute path.
- **pwd** with no options.
- **export** with no options.
- **unset** with no options.
- **env** with no options or arguments.
- **exit** with no options.

### Bonus
The minishell program has to implement:
- **&&** and **||** with parenthesis for priorities.
- **Wildcards* \* should work for the current working directory.

## How to make the executable ?
```bash
git clone https://github.com/Arawyn42/42_minishell
cd 42_minishell
make
```

## How to use ?
You just need to launch the minishell in a terminal, with the following command:
```bash
./minishell
```

You can also use the -c flag, like in bash, to execute only one command line into the minishell, like this:
```bash
./minishell -c "..."
```

Some features have been implemented even if the subject didn't ask for it. For exemple, the backslash *\\* works in several cases, **unclosed quotes** open a kind of here_doc, like in bash, **exit**'s builtin works with arguments, like the bash's exit...