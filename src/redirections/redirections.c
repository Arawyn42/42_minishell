/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 20:56:55 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Open the file given un parameter with the flags given in parameter.
 *	Change the standars input by the file descriptor returned by the open
 *	function.
 *	If the open function returns -1, prints an error and the standars input
 *	is not changed.
*/
int	input_redirection(char *file)
{
	int		fd;

	file = trim_one(file, "\'\"");
	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(file, 2);
		perror("\1");
		g_exit_status = 1;
		free(file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	free(file);
	return (fd);
}

/*
 *	Open the file given un parameter with the flags given in parameter.
 *	Change the standars output by the file descriptor returned by the open
 *	function.
 *	If the open function returns -1, prints an error and the standars output
 *	is not changed.
*/
int	output_redirection(char *file, int oflags)
{
	int		fd;

	// file = parse_line(file, NULL, 1);
	file = trim_one(file, "\'\"");
	fd = open(file, oflags, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(file, 2);
		perror("\1");
		g_exit_status = 1;
		free(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	free(file);
	return (fd);
}
