/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/05 18:40:45 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	WORK IN PROGRESS
 *	Takes the command line and the position of the pipe, and execute the
 *	pipe accordingly.
*/
// void	ft_pipe(char *cmd_line, int pipe_pos)
// {
// 	int		pide_fd;
// 	pid_t	pid;

// 	if 
// }

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