/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:43:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:00:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_double_quotes(char *str)
{
	int	dq;
	int	insq;
	int	indq;
	int	i;

	dq = 0;
	insq = 0;
	indq = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] != '\\') && !insq && str[i] == '\"')
			dq++;
		in_or_out_quotes(str, &insq, &indq, i);
		i++;
	}
	return (dq);
}

int	count_single_quotes(char *str)
{
	int	sq;
	int	insq;
	int	indq;
	int	i;

	sq = 0;
	insq = 0;
	indq = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] != '\\' || insq) && !indq && str[i] == '\'')
			sq++;
		in_or_out_quotes(str, &insq, &indq, i);
		i++;
	}
	return (sq);
}

void	in_or_out_quotes(char *line, int *singleq, int *doubleq, int i)
{
	if ((i == 0 || line[i - 1] != '\\') && line[i] == '\''
		&& *singleq == 0 && *doubleq == 0)
		*singleq = 1;
	else if (line[i] == '\'' && *singleq == 1)
		*singleq = 0;
	else if ((i == 0 || line[i - 1] != '\\')
		&& line[i] == '\"' && *doubleq == 0 && *singleq == 0)
		*doubleq = 1;
	else if ((i == 0 || line[i - 1] != '\\')
		&& line[i] == '\"' && *doubleq == 1)
		*doubleq = 0;
}

char	*get_dollar_var(t_data *data, int *i, int *var_len)
{
	int		k;
	char	*var;

	k = -1;
	var = ft_substr(data->line, *i, *var_len);
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
			return (var);
		}
	}
	return (NULL);
}

int	parse_conditions(char *line, int i, int insq, int indq)
{
	if (i >= 1 && line[i] == '?' && line[i - 1] == '$')
		return (0);
	if (line[i] == '~' && !insq && !indq && line[i - 1] == ' '
		&& (line[i + 1] == ' ' || line[i + 1] == '/' || !line[i + 1]))
		return (0);
	if (line[i] == '*' && !insq && !indq && (i == 0 || line[i - 1] != '\\'))
		return (0);
	if (line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
		return (1);
	if (i > 0 && line[i - 1] == '\\' && !insq)
		return (1);
	if (insq && line[i] != '\'')
		return (1);
	if (indq && line[i] != '\"' && line[i] != '\\')
		return (1);
	if (line[i] == '\\' && indq && (line[i + 1] == '\'' || line[i + 1] == ' '))
		return (1);
	return (0);
}
