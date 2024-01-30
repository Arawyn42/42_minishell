/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/30 11:12:16 by nsalles          ###   ########.fr       */
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
		line = get_next_line(STDIN_FILENO);
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

void	here_doc(char **cmds, int *index, t_data *data)
{
	int	pid;
	int	pipe_fd[2];
	int	saved_stdin;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	if (!cmds[(*index) + 1])
		return (redirection_error_message());
	pipe(pipe_fd);
	pid = fork();
	g_pid = pid;
	if (pid == 0)
		here_doc_reading(parse_line(cmds[(*index) + 1], data->env), pipe_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	waitpid(pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	data->line = parse_line(ft_strdup(cmds[*index]), data->env);
	(*index)++;
	if (!g_sigint && !builtin_launcher(data))
		ft_fork_exec(data->line, data->env);
	if (g_sigint)
		free(data->line);
	dup2(saved_stdin, STDIN_FILENO);
}

/****************************** To do the pipes *****************************/
/* 1. In child process, link the pipe output to the standard output (1), 	*/
/*	  then execute the current cmd (av[i]).									*/
/* 2. In parent process, link the pipe input to the standard input (0).		*/
/****************************************************************************/
void	ft_pipe(char *cmd, t_data *data)
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
		data->line = parse_line(ft_strdup(cmd), data->env);
		if (builtin_launcher(data))
			exit(EXIT_SUCCESS);
		else
			ft_exec(data->line, data->env);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	wait(NULL);
	dup2(saved_stdout, STDOUT_FILENO);
}
