/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 20:23:39 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Prints a string on the standard output.
*/
static void	echo_write(char *line, int i)
{
	while (line[i])
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
void	ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (!data->line[0])
		return ;
	if (!data->line[4])
		write(1, "\n", 1);
	else if (data->line[5] == '-' && data->line[6] == 'n'
		&& (data->line[7] == ' ' || !data->line[7]))
	{
		i = 8;
		echo_write(data->line, i);
	}
	else
	{
		i = 5;
		echo_write(data->line, i);
		write(1, "\n", 1);
	}
	g_exit_status = 0;
}
