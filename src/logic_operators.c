/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:54:57 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 03:05:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition(char *operator)
{
	if (!operator)
		return (1);
	return ((!ft_strncmp(operator, "&&", 2) && !g_exit_status) || 
			(!ft_strncmp(operator, "||", 2) && g_exit_status));
}

int	skip_parenthesis(char *str, int pos)
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
	return (pos);
}

//	Change cette fonction en mode 'get_word' avec un substr et tout.
//	Comme dans split, skip le start si tu es dans les parentheses qui ne  
//		doivent pas être interprété.
//	Le mot commence à 0 (sauf dans le cas de parentheses skip) et fini au
//		prochain operateur ou à la fin du str.
static char	*get_command(char *str, int *start, char *last_operator)
{
	char		*res;
	int			len;

	len = -1;
	while (len == -1 || str[*start + len])
	{
		len++;
		if (!condition(last_operator) && str[*start + len] == '(')
		{
			*start = skip_parenthesis(str, *start + len + 1);
			len = 0;
		}
		if (!ft_strncmp(&str[*start + len], "&&", 2) ||
			!ft_strncmp(&str[*start + len], "||", 2))
		{
			if (condition(last_operator))
				break ;
			last_operator = &str[*start + len];
			*start = *start + len + 2;
			len = 0;
		}
	}
	if (condition(last_operator))
		res = ft_substr(str, *start, len);
	else
		res = NULL;
	// printf("start = %d\n", *start);
	// printf("len = %d\n", len);
	// printf("line = %s\n", res);
	// printf("last operator = %s\n", last_operator);
	*start = *start + len;
	if (!str[*start] || len == 0)
		*start = -1;
	return (res);
}

/*
 *	Cuts the commands from logic operators && and || then run them.
*/
void	parse_logic_operators(t_data *data)
{
	char	*line; // crash one space
	int		start;

	start = 0;
	line = ft_strtrim(data->line, " ");
	free(data->line);
	data->line = get_command(line, &start, NULL);
	command_launcher(data);
	while (start != -1)
	{
		start += 2;
		data->line = get_command(line, &start, &line[start - 2]);
		if (data->line)
			command_launcher(data);
	}
	data->line = line;
}
