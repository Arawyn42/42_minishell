/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:42:06 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 14:44:13 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Returns the corresponding value from an environnement variable.
 *	If the variable is not found, returns NULL.
*/
static char	*get_dollar_var(t_data *data, int *i, int *var_len)
{
	int		k;
	char	*var;

	k = -1;
	var = ft_substr(data->line, *i, *var_len);
	(*i) += *var_len;
	while (data->env && data->env[++k])
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
	return (free(var), NULL);
}

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
		&& data->line[*i + j] != '/' && data->line[*i + j] != '\\'
		&& data->line[*i + j] != '$' && data->line[*i + j] != '\n')
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
void	dollar_var_len(t_data *data, int *i, int *len)
{
	char	*ex_stat;

	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0'
		|| !data->env)
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
	if (data->line[*i] == '$')
		dollar_var_len(data, i, len);
}

/*
 *	Replaces the environnement variable name (preceded by '$') by its
 *	corresponding value.
*/
static void	parse_dollar_value(t_data *data, char *new_line, int *i, int *j)
{
	char	*var;
	int		k;

	k = 0;
	while (data->line[*i + k] && data->line[*i + k] != ' '
		&& data->line[*i + k] != '\'' && data->line[*i + k] != '\"'
		&& data->line[*i + k] != '/' && data->line[*i + k] != '\\'
		&& data->line[*i + k] != '$' && data->line[*i + k] != '\n')
		k++;
	var = get_dollar_var(data, i, &k);
	k = 0;
	while (var && var[k])
	{
		new_line[*j] = var[k];
		(*j)++;
		k++;
	}
	if (var)
		free(var);
}

/*
 *	If '$?' is found, replaces it by the current exit status code.
 *	If '$' is followed by a numerical character, replaces it by nothing.
 *	In other cases, replaces the environnement variable by its value if
 *	the variable exists or by nothing if it doesn't.
*/
void	parse_dollar_var(t_data *data, char *new_line, int *i, int *j)
{
	char	*ex_stat;
	int		k;

	k = 0;
	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\"'
		|| data->line[*i + 1] == '\0' || !data->env)
		return ;
	(*i)++;
	if (data->line[*i] == '?')
	{
		ex_stat = ft_itoa(g_exit_status);
		while (ex_stat[k])
		{
			new_line[*j] = ex_stat[k];
			(*j)++;
			k++;
		}
		free(ex_stat);
	}
	else if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		parse_dollar_value(data, new_line, i, j);
	if (data->line[*i] == '$')
		parse_dollar_var(data, new_line, i, j);
}
