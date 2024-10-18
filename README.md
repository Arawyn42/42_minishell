<div align="center">
  <h1>⚙️ minishell (a <a href="https://42perpignan.fr/">42</a> project) ⚙️</h1>
  <p>Subject: <a href="en.subject.pdf">en.subject.pdf</a></p>
</div>

<div align="center">
  <h2>✅ Grade</h2>
  <img src="grade.png" alt="Grade">
</div><br>

## <div align="center">📄 Introduction</div>
This project consists in **reproducing the behaviour of bash**. We had to make a *mini bash*.
It had to be coded in **C language**, with a makefile compiling all the files together.
For this project, we had to work in team with another student. Special thanks to [Nico](https://github.com/Floperatok) who has been the perfect teammate for it! It taught us how to work together on the same github repository and on the same project. Each of us made his part to complete the other's part.

This project was done during 42 cursus at 42 Perpignan in January of 2024 with bonus.
<br><br>

## <div align="center">📒 Rules</div>
### <div align="center">📋 General rules</div>
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

### <div align="center">🔩 Builtins</div>
Your shell must implement the following builtins:
- **echo** with option -n.
- **cd** with only a relative or absolute path.
- **pwd** with no options.
- **export** with no options.
- **unset** with no options.
- **env** with no options or arguments.
- **exit** with no options.

### <div align="center">⭐ Bonus</div>
The minishell program has to implement:
- **&&** and **||** with parenthesis for priorities.
- **Wildcards* \* should work for the current working directory.
<br><br>

## <div align="center">💻 Usage</div>
Clone the repository and make the binary:
```bash
git clone https://github.com/Arawyn42/42_minishell
```
```bash
cd 42_minishell && make
```

Launch the program:
```bash
./minishell
```

You can also use the -c flag, like in bash, to execute only one command line into the minishell, like this:
```bash
./minishell -c "..."
```

Some features have been implemented even if the subject didn't ask for it. For exemple, the backslash *\\* works in several cases, **unclosed quotes** open a kind of here_doc, like in bash, **exit**'s builtin works with arguments, like the bash's exit...
