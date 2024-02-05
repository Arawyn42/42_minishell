/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:48:40 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 22:35:59 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Closes the current pipe fds, send an error message with perror then exits.
*/
void	ft_error_exit(int *pipe_fd, const char *msg)
{
	ft_close(pipe_fd);
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
 *	Closes the current pipe fds.
*/
void	ft_close(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
