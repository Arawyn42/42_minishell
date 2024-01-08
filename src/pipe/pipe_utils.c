/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:48:40 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/05 18:40:25 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Close the current pipe fds, send an error message with perror then exit */
void	ft_error_exit(int *pipe_fd, const char *msg)
{
	ft_close(pipe_fd);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_close(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
