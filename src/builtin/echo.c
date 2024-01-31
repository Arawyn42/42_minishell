/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 23:36:49 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Prints a string on the standard output.
*/
static void	echo_write(char *line, int i)
{
	if ((size_t) i > ft_strlen(line))
		return ;
	while (line && line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
}

/*
 *	Builtin: echo.
 *	Prints the arguments on the standard output after the input has been parsed.
 *	Can take the '-n' flag to print with no new line.
 *	Exit status code is 0 in all cases.
*/
void	ft_echo(char *command)
{
	int	i;

	i = 0;
	if (!command[0])
		return ;
	if (!command[4])
		write(1, "\n", 1);
	else if (command[5] == '-' && command[6] == 'n'
		&& (command[7] == ' ' || !command[7]))
	{
		i = 8;
		echo_write(command, i);
	}
	else
	{
		i = 5;
		echo_write(command, i);
		write(1, "\n", 1);
	}
	free(command);
	g_exit_status = 0;
}
