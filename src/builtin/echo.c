/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/03 00:38:03 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_dollar_path(t_data *data, int *i)
{
	char	*var;
	int		j;
	int		k;

	j = 0;
	k = -1;
	while (data->line[*i + j] && data->line[*i + j] != ' '
		&& data->line[*i + j] != 34)
		j++;
	var = ft_substr(data->line, *i, j);
	while (data->env[++k])
	{
		if (!ft_strncmp(data->env[k], var, j))
		{
			j = 0;
			while (data->env[k][j] && data->env[k][j] != '=')
				j++;
			j++;
			while (data->env[k][j])
				write(1, &data->env[k][j++], 1);
		}
	}
	*i += ft_strlen(var);
	if (var)
		free(var);
}

static void	echo_dollar(t_data *data, int *i)
{
	(*i)++;
	if (data->line[*i] == ' ' || data->line[*i] == '\0')
	{
		write(1, "$", 1);
		while(data->line[*i] == ' ')
			(*i)++;
		if (data->line[*i])
		write(1, " ", 1);
	}
	else if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		echo_dollar_path(data, i);
}

static void	echo_nflag(t_data *data, int i)
{
	int	in_single_quotes;
	int	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while(data->line[i])
	{
		if (data->line[i] == 39 && in_single_quotes == 0)
			in_single_quotes = 1;
		else if (data->line[i] == 39 && in_single_quotes == 1)
			in_single_quotes = 0;
		if (data->line[i] == 34 && in_double_quotes == 0)
			in_double_quotes = 1;
		else if (data->line[i] == 34 && in_double_quotes == 1)
			in_double_quotes = 0;
		if (data->line[i] == '$' && !in_single_quotes)
			echo_dollar(data, &i);
		if ((data->line[i] != 39 && data->line[i] != 34)
			|| (in_single_quotes && data->line[i] != 39)
			|| (in_double_quotes && data->line[i] != 34))
			write(1, &data->line[i], 1);
		i++;
	}
}

void	echo(t_data *data)
{
	if (count_double_quotes(data->line) % 2
		|| count_single_quotes(data->line) % 2)
	{
		ft_putstr("minishell: echo: quotes error\n", 2);
		return ;
	}
	if (data->line[5] == '-' && data->line[6] == 'n' && data->line[7] == ' ')
		echo_nflag(data, 8);
	else
	{
		echo_nflag(data, 5);
		write(1, "\n", 1);
	}
}
