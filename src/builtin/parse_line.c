/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:46:43 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 19:39:09 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_dollar_var(t_data *data, int *i, int *var_len)
{
	int		k;
	char	*var;

	k = -1;
	var = ft_substr(data->line, *i, *var_len);
	printf("Au début, var = %s\n", var);
	(*i) += *var_len;
	while (data->env[++k])
	{
		if (!ft_strncmp(data->env[k], var, *var_len))
		{
			*var_len = 0;
			while (data->env[k][*var_len] && data->env[k][*var_len] != '=')
				(*var_len)++;
			(*var_len)++;
			if (var)
				free(var);
			var = ft_substr(data->env[k], *var_len,
				ft_strlen(data->env[k]) - *var_len);
		}
	}
	return (var);
}

static void	parse_dollar_value(t_data *data, char *new_line, int *i, int *j)
{
	char	*var;
	int		k;

	k = 0;
	while (data->line[*i + k] && data->line[*i + k] != ' '
		&& data->line[*i + k] != '\'' && data->line[*i + k] != '\"'
		&& data->line[*i + k] != '/' && data->line[*i + k] != '\\')
		k++;
	var = get_dollar_var(data, i, &k);
	k = 0;
	while(var[k])
	{
		new_line[*j] = var[k];
		(*j)++;
		k++;
	}
	if (var)
		free(var);
}

static void	parse_dollar_var(t_data *data, char *new_line, int *i, int *j)
{
	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0')
		return ;
	(*i)++;
	if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		parse_dollar_value(data, new_line, i, j);
}

static void	parse_spaces(char *line, char *new_line, int *i, int *j)
{
	if (*i == 0 || (line[*i - 1] != '\\' && line[*i - 1] != ' '))
	{
		new_line[*j] = line[*i];
		(*j)++;
		while (line[*i] == ' ')
				(*i)++;
	}
}

static void	parsed_line(t_data *data, char *new_line, int *in_singleq, int *in_doubleq)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (data->line[++i])
	{
		if (data->line[i] == ' ' && !(*in_singleq) && !(*in_doubleq))
			parse_spaces(data->line, new_line, &i, &j);
		if ((data->line[i] == '\'' || data->line[i] == '\"')
			&& data->line[i - 1] != '\\')
			in_or_out_quotes(data->line, in_singleq, in_doubleq, i++);
		if (data->line[i] == '\\' && !(*in_singleq) && !(*in_doubleq))
			i++;
		if (data->line[i] == '$' && !(*in_singleq)
			&& (i == 0 || data->line[i - 1] != '\\'))
			parse_dollar_var(data, new_line, &i, &j);
		if ((data->line[i] != '\"' && data->line[i] != '\'')
			|| (i > 0 && data->line[i - 1] == '\\')
			|| (in_singleq && data->line[i] != '\'')
			|| (in_doubleq && data->line[i] != '\"'))
			new_line[j++] = data->line[i];
	}
}

void	parse_line(t_data *data)
{
	char	*new_line;
	int		in_singleq;
	int		in_doubleq;
	int		len;

	in_singleq = 0;
	in_doubleq = 0;
	len = 0;
	new_line_len(data, &len);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return ;
	parsed_line(data, new_line, &in_singleq, &in_doubleq);
	free(data->line);
	data->line = new_line;
}
