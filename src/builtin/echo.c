/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/05 20:35:39 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_write(char *line, int i)
{
	while(line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
}

void	echo(t_data *data)
{
	int	i;

	i = 0;
	if (count_double_quotes(data->line) % 2
		|| count_single_quotes(data->line) % 2)
	{
		ft_putstr("minishell: echo: quotes error\n", 2);
		return ;
	}
	parse_line(data);
	if (data->line[5] == '-' && data->line[6] == 'n' && data->line[7] == ' ')
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
}
