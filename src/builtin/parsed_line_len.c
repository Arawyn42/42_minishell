/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_line_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:59:34 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/09 17:50:10 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar_value_len(t_data *data, int *i, int *len)
{
	char	*var;
	int		j;

	j = 0;
	while (data->line[*i + j] && data->line[*i + j] != ' '
		&& data->line[*i + j] != '\'' && data->line[*i + j] != '\"'
		&& data->line[*i + j] != '/' && data->line[*i + j] != '\\')
		j++;
	var = get_dollar_var(data, i, &j);
	if (var)
	{
		*len += ft_strlen(var);
		free(var);
	}
}

static void	dollar_var_len(t_data *data, int *i, int *len)
{
	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0')
		return ;
	(*i)++;
	if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		dollar_value_len(data, i, len);
}

static void	spaces_len(char *line, int *i)
{
	while (line[*i] == ' ' && line[*i + 1] == ' ')
		(*i)++;
}

void	new_line_len(t_data *data, int *len)
{
	int	i;
	int	in_singleq;
	int	in_doubleq;

	in_singleq = 0;
	in_doubleq = 0;
	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == ' ' && !in_singleq && !in_doubleq)
			spaces_len(data->line, &i);
		if (data->line[i] == '\\' && !in_singleq && !in_doubleq)
			i++;
		if (data->line[i] == '$' && !in_singleq
			&& (i == 0 || data->line[i - 1] != '\\'))
			dollar_var_len(data, &i, len);
		if (parse_conditions(data->line, i, in_singleq, in_doubleq))
			(*len)++;
		if ((data->line[i] == '\'' || data->line[i] == '\"'))
			in_or_out_quotes(data->line, &in_singleq, &in_doubleq, i);
		i++;
	}
}
