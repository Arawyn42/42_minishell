/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/31 13:55:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_error(char *limiter)
{
	if (!g_sigint)
	{
		ft_putstr("minishell: warning: here-document at line delimited by", 2);
		ft_putstr(" end-of-file (wanted `", 2);
		ft_putstr(limiter, 2);
		ft_putstr("')\n", 2);
		g_exit_status = 2;
	}
	else
	{
		g_exit_status = 130;
	}
}

static void	here_doc_reading(char *limiter, int *pipe_fd)
{
	char	*line;

	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(STDIN_FILENO); // change for readline for history
		if (!line)
		{
			here_doc_error(limiter);
			break ;
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) && \
			ft_strlen(limiter) == ft_strlen(line) - 1)
			break ;
		ft_putstr(line, pipe_fd[1]);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	get_next_line(-1);
	close(pipe_fd[1]);
	exit(g_exit_status);
}

void	here_doc(t_data *data, int *i)
{
	int	pid;
	int	pipe_fd[2];
	int	saved_stdin;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	if (!data->command[*i + 1])
		return (ft_putstr("!!!PARSING ERROR!!!\n", 2), exit(EXIT_FAILURE)); // remove
	pipe(pipe_fd);
	pid = fork();
	g_pid = pid;
	if (pid == 0)
		here_doc_reading(data->command[*i + 1], pipe_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	waitpid(pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	if (data->command[*i - 1])
		if (!g_sigint && !builtin_launcher(data->command[*i - 1], data))
			ft_fork_exec(data->command[*i - 1], data);
	(*i)++;
	dup2(saved_stdin, STDIN_FILENO);
}

/****************************** To do the pipes *****************************/
/* 1. In child process, link the pipe output to the standard output (1), 	*/
/*	  then execute the current cmd (av[i]).									*/
/* 2. In parent process, link the pipe input to the standard input (0).		*/
/****************************************************************************/
void	ft_pipe(t_data *data, int *i)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	pipe(pipe_fd);
	pid = fork();
	g_pid = pid;
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close(pipe_fd);
		if (!data->command[*i - 1])
			return (ft_putstr("!!PARSING ERROR!!\n", 2), exit(EXIT_FAILURE)); // remove
		if (builtin_launcher(data->command[*i - 1], data))
			exit(EXIT_SUCCESS); // code d'exit ?
		else
			ft_exec(data->command[*i - 1], data);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	wait(NULL);
	dup2(saved_stdout, STDOUT_FILENO);
}
