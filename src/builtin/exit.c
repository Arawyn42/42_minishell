/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:35:30 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/16 15:49:05 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(t_data *data)
{
	char	*line;

	line = parse_line(ft_strdup(data->line), data->env);
	if (!ft_strcmp(line, "exit") || !ft_strncmp(data->line, "exit ", 5))
	{
		free(line);
		ft_exit(data);
	}
	return (0);
}

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
		exit(EXIT_SUCCESS);
	}
}

/* exit builtin */
void	ft_exit(t_data *data)
{
	int	i;

	i = 5;
	if (!ft_strncmp(data->line, "exit ", 5))
	{
		while (data->line[i])
		{
			check_exit_args(data, &i);
			i++;
		}
	}
	ft_putstr("exit\n", 1);
	free_all(data);
	exit(EXIT_SUCCESS);
}
