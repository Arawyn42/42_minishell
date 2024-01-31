/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:35:30 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 23:37:13 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Returns an error and exits the program with a 2 status exit code
 *	if arguments are incorrect. Arguments for the exit command should be
 *	numerical only.
*/
static void	check_exit_args(char *command, t_data *data, int *i)
{
	if (command[*i] != ' '
		&& (command[*i] < '0' || command[*i] > '9'))
	{
		*i = 5;
		while (command[*i] == ' ')
			(*i)++;
		ft_putstr("exit\n", 1);
		ft_putstr("minishell: exit: ", 2);
		while (command[*i])
			write(2, &command[(*i)++], 1);
		ft_putstr(": numeric argument required\n", 2);
		free_all(data);
		g_exit_status = 2;
		exit(g_exit_status);
	}
}

/*
 *	Builtin: exit.
 *	Exits the program. If no argument is specified, exit status code is 0.
 *	If a numerical argument is specified, exit status code is the corresponding
 *	entry modulo 256, as in bash.
*/
void	ft_exit(char *command, t_data *data)
{
	int		i;
	char	*arg;

	i = 5;
	if (!ft_strncmp(command, "exit ", 5))
	{
		if (command[i] == '-')
			i++;
		while (command[i])
		{
			check_exit_args(command, data, &i);
			i++;
		}
	}
	g_exit_status = 0;
	if (command[4] && command[5])
	{
		arg = ft_substr(command, 5, ft_strlen(command) - 5);
		g_exit_status = ft_atoi(arg) % 256;
		free(arg);
	}
	ft_putstr("exit\n", STDERR_FILENO);
	free_all(data);
	free(command);
	exit(g_exit_status);
}
