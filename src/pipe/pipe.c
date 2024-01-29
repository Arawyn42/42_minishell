/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 23:14:05 by nsalles          ###   ########.fr       */
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
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, limiter))
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
	int	status;

	if (!cmds[(*index) + 1])
	{
		ft_putstr("minishell: syntax error: ", 2);
		return (ft_putstr("unexpected pipe or redirection\n", 2));
	}
	if (pipe(pipe_fd) == -1)
		return (ft_putstr("minishell: unexpected fork error", 2));
	pid = fork();
	g_pid = pid;
	if (pid == -1)
		ft_error_exit(pipe_fd, "minishell: unexpected fork error");
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

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr("minishell: unexpected fork error", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	g_pid = pid;
	if (pid == -1)
		ft_error_exit(pipe_fd, "minishell: unexpected fork error");
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
}
