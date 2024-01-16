/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:35:30 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/16 19:47:17 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exit_args(t_data *data, int *i)
{
	if (data->line[*i] != ' '
		&& (data->line[*i] < '0' || data->line[*i] > '9'))
	{
		*i = 5;
		while (data->line[*i] == ' ')
			(*i)++;
		ft_putstr("exit\n", 1);
		ft_putstr("minishell: exit: ", 2);
		while (data->line[*i])
			write(2, &data->line[(*i)++], 1);
		ft_putstr(": numeric argument required\n", 2);
		free_all(data);
		error_value = 2;
		exit(error_value);
	}
}

/* exit builtin */
void	ft_exit(t_data *data)
{
	int	i;
	char	*arg;

	i = 5;
	if (!ft_strncmp(data->line, "exit ", 5))
	{
		if (data->line[i] == '-')
			i++;
		while (data->line[i])
		{
			check_exit_args(data, &i);
			i++;
		}
	}
	error_value = 0;
	if (data->line[5])
	{
		arg = ft_substr(data->line, 5, ft_strlen(data->line) - 5);
		error_value = ft_atoi(arg) % 256;
		free(arg);
	}
	ft_putstr("exit\n", 1);
	free_all(data);
	exit(error_value);
}
