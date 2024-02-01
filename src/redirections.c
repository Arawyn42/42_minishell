/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/01 14:18:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redirection(char *file)
{
	int		fd;

	if (!file)
	{
		ft_putstr("!!!PARSING ERROR!!!\n", 2);
		exit(EXIT_FAILURE); // remove
	}
	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(file, 2);
		perror("\1");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	return (fd);
}

int	output_redirection(char *file, int oflags)
{
	int		fd;

	if (!file)
	{
		ft_putstr("!!!PARSING ERROR!!!\n", 2);
		exit(EXIT_FAILURE); // remove
	}
	fd = open(file, oflags, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(file, 2);
		perror("\1");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	return (fd);
}
