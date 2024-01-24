/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:44:46 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/23 21:17:20 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*unclosed_double(t_data *data)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
		{
			ft_putstr("minishell: unexpected EOF while looking for ", 2);
			ft_putstr("matching `\"'\nminishell: syntax error: unexpected", 2);
			ft_putstr(" end of file\n", 2);
			free(new_line);
			g_exit_status = 2;
			return (add_history(data->line), free(data->line), ft_strdup(""));
		}
		line = ft_strjoin(data->line, "\n");
		free(data->line);
		data->line = ft_strjoin(line, new_line);
		free(new_line);
		free(line);
		if (count_double_quotes(data->line) % 2 == 0)
			return (add_history(data->line), data->line);
	}
	return (data->line);
}

static char	*unclosed_single(t_data *data)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
		{
			ft_putstr("minishell: unexpected EOF while looking for ", 2);
			ft_putstr("matching `\''\nminishell: syntax error: unexpected", 2);
			ft_putstr(" end of file\n", 2);
			free(new_line);
			g_exit_status = 2;
			return (add_history(data->line), free(data->line), ft_strdup(""));
		}
		line = ft_strjoin(data->line, "\n");
		free(data->line);
		data->line = ft_strjoin(line, new_line);
		free(new_line);
		free(line);
		if (count_single_quotes(data->line) % 2 == 0)
			return (add_history(data->line), data->line);
	}
	return (data->line);
}

int	is_unclosed_quotes(t_data *data)
{
	if (count_double_quotes(data->line) % 2 == 0
		&& count_single_quotes(data->line) % 2 == 0)
		return (0);
	return (1);
}

char	*unclosed_quotes(t_data *data)
{
	int		i;

	i = 0;
	if (!is_unclosed_quotes(data))
		return (data->line);
	while (data->line[i])
	{
		if (data->line[i] == '\'')
		{
			data->line = unclosed_single(data);
			break ;
		}
		else if (data->line[i] == '\"')
		{
			data->line = unclosed_double(data);
			break ;
		}
		i++;
	}
	return (data->line);
}
