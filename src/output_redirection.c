/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/11 12:50:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_redirection(char *file, t_data *data)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		write(2, file, ft_strlen(file));
		perror("");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	if (!command_launcher(data))
		ft_fork_exec(data->line, data->env);
}
