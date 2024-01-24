/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:54:57 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/24 01:34:11 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	logic_operator_pos(char *str)
{
	static int	pos = 0;

	while (str[pos])
	{
		if (!ft_strncmp(&str[pos], "&&", 2) || !ft_strncmp(&str[pos], "||", 2))
		{
			pos += 2;
			return (pos);
		}
		pos++;
	}
	pos = 0;
	return (-1);
}

/*
 *	Cuts the commands from logic operators && and || then run them.
*/
void	parse_logic_operators(t_data *data)
{
	int 	pos;
	int		old;
	char	*line;

	line = ft_strtrim(data->line, " ()");
	pos = logic_operator_pos(line);
	old = 0;
	data->line = ft_substr(line, old, pos - 2 - old);
	command_launcher(data);
	while (pos != -1)
	{
		old = pos;
		pos = logic_operator_pos(line);
		if (pos == -1)
			data->line = ft_substr(line, old, ft_strlen(line) - old);
		else
			data->line = ft_substr(line, old, pos - 2 - old);
		if ((!ft_strncmp(&line[old - 2], "&&", 2) && !g_exit_status) ||
			(!ft_strncmp(&line[old - 2], "||", 2) && g_exit_status))
			command_launcher(data);
	}
}
