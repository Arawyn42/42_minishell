/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 19:42:33 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int	i;

	i = 0;
	parse_line(data);
	if (count_double_quotes(data->line) % 2
		|| count_single_quotes(data->line) % 2)
	{
		ft_putstr("minishell: echo: quotes error\n", 2);
		return ;
	}
	if (data->line[5] == '-' && data->line[6] == 'n' && data->line[7] == ' ')
	{
		i = 8;
		while(data->line[i])
			write(1, &data->line[i++], 1);
	}
	else
	{
		i = 5;
		while(data->line[i])
			write(1, &data->line[i++], 1);
		write(1, "\n", 1);
	}
}
