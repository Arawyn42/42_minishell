# 42_minishell

# <div align="center">⚙️ pipex (a [42](https://42perpignan.fr/) project) ⚙️</div>

## Grade
![drenassi's 42 pipex Score](https://badge42.coday.fr/api/v2/clph33bao098101t6vnzqbe17/project/3398019)

## Introduction
This project consists in reproducing the behaviour of the pipe `|` in bash.

Done in 42 cursus at 42 Perpignan, in November of 2023 with bonus.

## How to make the executable ?
```bash
git clone https://github.com/Arawyn42/42_pipex
cd 42_pipex
```
### Normal version
```bash
make
make clean
```

### Bonus version
```bash
make bonus
make clean
```

## How to use ?
### Normal version
The following command :
```bash
./pipex file1 cmd1 cmd2 file2
```
is the equivalent of the bash command:
```bash
< file1 cmd1 | cmd2 > file2
```
### Bonus version
The bonus build allows multi pipes, like this:
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```

With the bonus build, it is also possible to perform a **here_doc** pipe, like this:
```bash
./pipex here_doc LIMITER cmd1 cmd2 ... cmdN outfile
```
where LIMITER correspond to the stop keyword of the here_doc. By convention, it's *EOF*, for End Of File.
