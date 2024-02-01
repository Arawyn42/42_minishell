/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:43:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/01 19:24:29 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Returns the number of double quotes detected in a string, according to
 *	the bash's quotes rules.
*/
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

/*
 *	Returns the number of single quotes detected in a string, according to
 *	the bash's quotes rules.
*/
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

/*
 *	Checks if we are in or out single quotes or double quotes, at the index i.
*/
void	in_or_out_quotes(const char *line, int *singleq, int *doubleq, int i)
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
