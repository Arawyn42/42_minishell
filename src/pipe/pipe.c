/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 13:45:51 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pipe_command(char **command, int i) // not used
{
	i--;
	while (i && command[i][0] != '>')
	{
		if (command[i][0] != '<' && (i - 1 < 1 ||
			!ft_strchr("><|", command[i - 1][0])))
			return (command[i]);
		i--;
	}
	return (NULL);
}

static void	here_doc_error(char *limiter)
{
	if (!g_sigint)
	{
		ft_putstr("\nminishell: warning: here-document at line delimited", 2);
		ft_putstr(" by end-of-file (wanted `", 2);
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
	}
	if (line)
		free(line);
	free(limiter);
	get_next_line(-1);
	close(pipe_fd[1]);
	exit(g_exit_status);
}

int	here_doc(char *limiter, t_data *data)
{
	int		pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		limiter = ft_strdup(limiter);
		free_all(data);
		here_doc_reading(limiter, pipe_fd);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	waitpid(pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	return (pipe_fd[0]);
}

/****************************** To do the pipes *****************************/
/* 1. In child process, link the pipe output to the standard output (1), 	*/
/*	  then execute the current cmd (av[i]).									*/
/* 2. In parent process, link the pipe input to the standard input (0).		*/
/****************************************************************************/

void	ft_pipe(int command_pos, t_data *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (data->input == -1 || data->output == -1)
		{
			free_all(data);
			exit(EXIT_FAILURE);
		}
		if (data->output == 1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close(pipe_fd);
		if (builtin_launcher(data->command[command_pos], data))
		{
			free_all(data);
			exit(EXIT_SUCCESS); // code d'exit ?
		}
		else
			ft_exec(data->command[command_pos], data);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close(pipe_fd);
	if (data->input == -1)
		data->input = 1;
	if (data->output == -1)
		data->output = 1;
	wait(NULL);
}
