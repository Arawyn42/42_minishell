/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_line_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:59:34 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 19:14:45 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_or_out_quotes(char *line, int *singleq, int *doubleq, int i)
{
	if ((i == 0 || line[i - 1] != '\\') && line[i] == '\'' && *singleq == 0)
		*singleq = 1;
	else if ((i == 0 || line[i - 1] != '\\')
		&& line[i] == '\'' && *singleq == 1)
		*singleq = 0;
	else if ((i == 0 || line[i - 1] != '\\')
		&& line[i] == '\"' && *doubleq == 0)
		*doubleq = 1;
	else if ((i == 0 || line[i - 1] != '\\')
		&& line[i] == '\"' && *doubleq == 1)
		*doubleq = 0;
}

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
	*len += ft_strlen(var);
	if (var)
		free(var);
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

static void	spaces_len(char *line, int *i, int *len)
{
	if (*i == 0 || (line[*i - 1] != '\\' && line[*i - 1] != ' '))
	{
		while (line[*i] == ' ')
				(*i)++;
		(*len)++;
	}
}

void	new_line_len(t_data *data, int *len)
{
	int	i;
	int	in_singleq;
	int	in_doubleq;

	in_singleq = 0;
	in_doubleq = 0;
	i = -1;
	while (data->line[++i])
	{
		if (data->line[i] == ' ' && !in_singleq && !in_doubleq)
			spaces_len(data->line, &i, len);
		if ((data->line[i] == '\'' || data->line[i] == '\"')
			&& data->line[i - 1] != '\\')
			in_or_out_quotes(data->line, &in_singleq, &in_doubleq, i++);
		if (data->line[i] == '\\' && !in_singleq && !in_doubleq)
			i++;
		if (data->line[i] == '$' && !in_singleq
			&& (i == 0 || data->line[i - 1] != '\\'))
			dollar_var_len(data, &i, len);
		if ((data->line[i] != '\"' && data->line[i] != '\'')
			|| (i > 0 && data->line[i - 1] == '\\')
			|| (in_singleq && data->line[i] != '\'')
			|| (in_doubleq && data->line[i] != '\"'))
			(*len)++;
	}
}
