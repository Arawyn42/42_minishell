/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_line_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:59:34 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 23:14:07 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Calculates the length of the corresponding value from an environnement
 *	variable and modifies the total length's pointer of the parsed
 *	string accordingly.
*/
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

/*
 *	Calculates the length of the parsed string resulted from the dollar '$'
 *	environnement variable and modifies the total length's pointer
 *	of the parsed string accordingly.
*/
static void	dollar_var_len(t_data *data, int *i, int *len)
{
	char	*ex_stat;

	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0')
		return ;
	(*i)++;
	if (data->line[*i] == '?')
	{
		ex_stat = ft_itoa(g_exit_status);
		*len += ft_strlen(ex_stat);
		free(ex_stat);
	}
	else if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		dollar_value_len(data, i, len);
}

/*
 *	Calculates the length of the HOME path and modifies the total length's
 *	pointer of the parsed string accordingly.
*/
static void	tilde_len(t_data *data, int *i, int *len)
{
	char	*home_path;

	if (data->line[*i + 1])
		(*i)++;
	home_path = get_home_path(data);
	if (home_path)
	{
		*len += ft_strlen(home_path);
		free(home_path);
	}
}

/*
 *	Replaces following multiple spaces by one space in the parsed string.
*/
void	parse_spaces(char *line, int *i)
{
	while (line[*i] == ' ' && line[*i + 1] == ' ')
		(*i)++;
}

/*
 *	Calculates the total length of the parsed string in order to allocate
 *	the good amount of memory space for it.
*/
void	new_line_len(t_data *data, int *len, int in_singleq, int in_doubleq)
{
	int	i;

	i = 0;
	while ((size_t) i < ft_strlen(data->line) && data->line[i])
	{
		if (data->line[i] == ' ' && !in_singleq && !in_doubleq)
			parse_spaces(data->line, &i);
		if (data->line[i] == '\\' && !in_singleq && !in_doubleq)
			i++;
		if (data->line[i] == '$' && !in_singleq && (i == 0
				|| data->line[i - 1] != '\\') && data->line[i + 1] != '~')
			dollar_var_len(data, &i, len);
		if (data->line[i] == '~' && !in_singleq && !in_doubleq
			&& data->line[i - 1] == ' ' && (data->line[i + 1] == ' '
				|| data->line[i + 1] == '/' || !data->line[i + 1]))
			tilde_len(data, &i, len);
		if (data->line[i] == '*' && !in_singleq && !in_doubleq
			&& (i == 0 || data->line[i - 1] != '\\'))
			wildcard_len(data, &i, len);
		if (parse_conditions(data->line, i, in_singleq, in_doubleq))
			(*len)++;
		if ((data->line[i] == '\'' || data->line[i] == '\"'))
			in_or_out_quotes(data->line, &in_singleq, &in_doubleq, i);
		i++;
	}
}
