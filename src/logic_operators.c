/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:54:57 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 23:34:03 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition(char *operator)
{
	if (!operator)
		return (1);
	return ((!ft_strncmp(operator, "&&", 2) && !g_exit_status) || \
		(!ft_strncmp(operator, "||", 2) && g_exit_status));
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

//	Change cette fonction en mode 'get_word' avec un substr et tout.
//	Comme dans split, skip le start si tu es dans les parentheses qui ne  
//		doivent pas être interprété.
//	Le mot commence à 0 (sauf dans le cas de parentheses skip) et fini au
//		prochain operateur ou à la fin du str.
// static char	*get_command(char *str, int *start, char *last_operator)
// {
// 	char		*res;
// 	int			len;

// 	len = -1;
// 	while (len == -1 || str[*start + len])
// 	{
// 		len++;
// 		if (!condition(last_operator) && str[*start + len] == '(')
// 		{
// 			*start = skip_parenthesis(str, *start + len + 1);
// 			len = 0;
// 		}
// 		if (!ft_strncmp(&str[*start + len], "&&", 2) ||
// 			!ft_strncmp(&str[*start + len], "||", 2))
// 		{
// 			if (condition(last_operator))
// 				break ;
// 			last_operator = &str[*start + len];
// 			*start = *start + len + 2;
// 			len = 0;
// 		}
// 	}
// 	if (condition(last_operator))
// 		res = ft_substr(str, *start, len);
// 	else
// 		res = NULL;
// 	// printf("start = %d\n", *start);
// 	// printf("len = %d\n", len);
// 	// printf("line = %s\n", res);
// 	// printf("last operator = %s\n", last_operator);
// 	*start = *start + len;
// 	if (!str[*start] || len == 0)
// 		*start = -1;
// 	return (res);
// }

static int	is_operator_found(char *str, char **last_ope, int *start, int i)
{
	if ((!ft_strncmp(&str[*start + i], "&&", 2) || \
		!ft_strncmp(&str[*start + i], "||", 2)) && \
		!is_in_quote(str, *start + i))
	{
		*start = *start + i + 2;
		if (condition(*last_ope))
		{
			*last_ope = &str[*start - 2];
			return (1);
		}
		*last_ope = &str[*start - 2];
	}
	return (0);
}

static char	*get_command(char *str, int str_len, int *start)
{
	static char	*last_operator = NULL;
	int			len;
	char		*res;
	int			is_found;

	res = NULL;
	if (*start == -1 || str == NULL)
		return (NULL);
	len = -1;
	while (*start + ++len < str_len)
	{
		is_found = is_operator_found(str, &last_operator, start, len);
		if (is_found > 0)
			return (ft_substr(str, *start - len - 2, len));
		else if (is_found == -1)
			return (NULL);
		if (!condition(last_operator) && str[*start + len] == '(')
			*start = skip_parenthesis(str, *start + len + 1, &len);
	}
	if (condition(last_operator))
		res = ft_substr(str, *start, str_len - *start);
	last_operator = NULL;
	*start = -1;
	return (res);
}

/*
 *	Cuts the commands from logic operators && and || then run them.
*/
void	parse_logic_operators(t_data *data)
{
	char	*line;
	int		line_len;
	int		start;

	start = 0;
	line = ft_strtrim(data->line, " ");
	line_len = ft_strlen(line);
	if (line_len == 0)
		return (free(line));
	if (is_open_parentheses(line))
		return (free(line));
	if (is_logic_operators_broken(line))
		return (free(line));
	free(data->line);
	data->line = get_command(line, line_len, &start);
	while (data->line)
	{
		command_launcher(data);
		data->line = get_command(line, line_len, &start);
	}
	free(line);
}
