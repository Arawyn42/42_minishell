/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:33:20 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 17:36:54 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	logic_operator_condition(char *operator)
{
	if (!operator)
		return (1);
	return ((!ft_strncmp(operator, "&&", 2) && !g_exit_status) || \
		(!ft_strncmp(operator, "||", 2) && g_exit_status));
}

int	is_operator_found(char *str, char **last_ope, int *start, int i)
{
	if ((!ft_strncmp(&str[*start + i], "&&", 2) || \
		!ft_strncmp(&str[*start + i], "||", 2)) && \
		!is_in_quote(str, *start + i))
	{
		*start = *start + i + 2;
		if (logic_operator_condition(*last_ope))
		{
			*last_ope = &str[*start - 2];
			return (1);
		}
		*last_ope = &str[*start - 2];
	}
	return (0);
}

int	skip_parenthesis(char *str, int pos, int *len)
{
	int	parenthesis_depth;

	parenthesis_depth = 1;
	while (parenthesis_depth != 0 && str[pos])
	{
		if (str[pos] == '(')
			parenthesis_depth++;
		else if (str[pos] == ')')
			parenthesis_depth--;
		pos++;
	}
	*len = 0;
	return (pos);
}

int	is_logic_operators_broken(char *line)
{
	int	i;
	int	last_operator_pos;
	int	is_ok;
	int	len;

	len = ft_strlen(line);
	i = -1;
	last_operator_pos = 0;
	is_ok = 0;
	while (++i < len)
	{
		if (!ft_strncmp(&line[i], "&&", 2) || !ft_strncmp(&line[i], "||", 2))
		{
			if (!is_ok && !is_in_quote(line, i))
				return (syntax_error_message(&line[i], 2), 1);
			is_ok = 0;
			last_operator_pos = i;
			i += 2;
		}
		if (line[i] && !ft_strchr(" ()", line[i]))
			is_ok = 1;
	}
	if (!is_ok)
		return (syntax_error_message(&line[last_operator_pos], 2), 1);
	return (0);
}

int	is_open_parentheses(char *line)
{
	int		parentheses_depth;
	int		i;

	parentheses_depth = 0;
	i = -1;
	while (line[++i])
	{
		if (!is_in_quote(line, i))
			parentheses_depth += (line[i] == '(') - (line[i] == ')');
		if (parentheses_depth < 0)
		{
			syntax_error_message(")", 1);
			return (1);
		}
	}
	if (parentheses_depth > 0)
	{
		syntax_error_message("(", 1);
		return (1);
	}
	return (0);
}
