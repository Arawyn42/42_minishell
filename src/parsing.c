/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotine <nikotine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nikotine          #+#    #+#             */
/*   Updated: 2024/01/02 17:32:12 by nikotine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 *	Returns the index of the next minishell's operator in the string,
 *	returns -1 if no operator is found.
*/
int	operator_pos(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (i);
	return (-1);
}

void input_handler(t_data *data)
{
	char	*line;
	int		pos;

	line = ft_strdup(data->line);
	pos = operator_pos(line);
	while (pos != -1)
	{
		free(data->line);
		data->line = ft_substr(line, 0, pos);
		command_launcher(data);
		line += pos;
		pos = operator_pos(line);
	}
	free(data->line);
	data->line = line;
	command_launcher(data);
}
