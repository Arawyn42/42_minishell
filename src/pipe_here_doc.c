/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:13:43 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/26 20:56:30 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************** To do the pipes *****************************/
/* 1. In child process, link the pipe output to the standard output (1), 	*/
/*	  then execute the current cmd (av[i]).									*/
/* 2. In parent process, link the pipe input to the standard input (0).		*/
/****************************************************************************/
void	ft_pipe(char *cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		ft_error_exit(pipe_fd, "ft_pipe: pipe error");
	pid = fork();
	if (pid == -1)
		ft_error_exit(pipe_fd, "ft_pipe: fork error");
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close(pipe_fd);
		ft_exec(cmd, env);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	wait(NULL);
}

/****** Duplicate the limiter for the here_doc and appends a '\n' to it *****/
static char	*ft_dup_limiter(const char *limiter)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(limiter) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (limiter[i])
	{
		res[i] = limiter[i];
		i++;
	}
	res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

/****************************** here_doc input ******************************/
/* 1. Get the input on the standard input (0), line by line.				*/
/* 2. Write it on the pipe output (write end of the pipe).					*/
/* 3. If the input is the LIMITER, exit the process.						*/
/****************************************************************************/
static void	ft_here_doc_input(char **av, int *pipe_fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_dup_limiter(av[2]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			ft_close(pipe_fd);
			exit(EXIT_SUCCESS);
		}
		ft_putstr(line, pipe_fd[1]);
		free(line);
	}
}

/***************************** here_doc handling ****************************/
/* 1. Check if there are at least 6 args.									*/
/* 2. Create a pipe_fd with the pipe function.								*/
/* 3. Create a child process with the fork function.						*/
/* 4. When in child process, call the ft_here_doc_input function to write	*/
/*	  on the pipe write end.												*/
/* 5. When in parent process, link the pipe read end to the standard input,	*/
/*	  then wait for the child process to finish.							*/
/****************************************************************************/
void	ft_here_doc(int ac, char **av)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac < 6)
	{
		ft_putstr("Too few parameters. Usage: ", STDOUT_FILENO);
		ft_putstr("./pipex here_doc LIMITER cmd cmd1 file\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (pipe(pipe_fd) == -1)
		ft_error_exit(pipe_fd, "here_doc: pipe error");
	pid = fork();
	if (pid == -1)
		ft_error_exit(pipe_fd, "here_doc: fork error");
	if (pid == 0)
		ft_here_doc_input(av, pipe_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	wait(NULL);
}
