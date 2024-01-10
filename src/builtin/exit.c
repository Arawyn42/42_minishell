/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:35:30 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/10 18:02:04 by drenassi         ###   ########.fr       */
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
		rl_clear_history();
		free(data->line);
		free_double_array(data->env);
		exit(EXIT_SUCCESS);
	}
}
/* exit builtin */
void	ft_exit(t_data *data)
{
	int	i;

	data->line = parse_line(data->line, data->env);
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
	rl_clear_history();
	free(data->line);
	free_double_array(data->env);
	exit(EXIT_SUCCESS);
}
