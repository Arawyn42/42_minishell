/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/06 13:59:50 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Closes the current pipe fds.
*/
static void	ft_close(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/*
 *	Print the error message in case of a ctrl-c of a ctrl-d during a here_doc.
 *	Setup the exit_status accordingly.
*/
static void	here_doc_error(char *limiter)
{
	if (!g_sigint)
	{
		ft_putstr("\nminishell: warning: here-document at line delimited", 2);
		ft_putstr(" by end-of-file (wanted `", 2);
		ft_putstr(limiter, 2);
		ft_putstr("')\n", 2);
	}
	else
	{
		g_exit_status = 130;
	}
}

/*
 *	Read in the standars input for the user to write until the user write
 *	the limiter and only the limiter on one line.
 *	Send the written text into a pipe for the command to read.
*/
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
	}
	if (line)
		free(line);
	free(limiter);
	get_next_line(-1);
	close(pipe_fd[1]);
	exit(g_exit_status);
}

/*
 *	Opens a here_doc with the End Of File being the string limiter.
*/
int	here_doc(char *limiter, t_data *data, int saved_stdin)
{
	int		pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
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

/*
 *	Opens a pipe and execute the command in command_pos.
 *	If data->input or data->output is -1, the command is not executed.
*/
void	ft_pipe(int command_pos, t_data *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (data->input == -1 || data->output == -1)
			exit_no_errors(data);
		if (data->output == 1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		ft_close(pipe_fd);
		if (builtin_launcher(data->command[command_pos], data))
			exit_no_errors(data);
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
