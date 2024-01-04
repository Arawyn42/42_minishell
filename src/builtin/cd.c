/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 20:12:08 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_data *data)
{
	char	*error_msg;
	char	*path;

	if (count_double_quotes(data->line) % 2
		|| count_single_quotes(data->line) % 2)
	{
		ft_putstr("minishell: cd: quotes error\n", 2);
		return ;
	}
	parse_line(data);
	path = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
	if (chdir(path) == -1)
	{
		error_msg = ft_strjoin("minishell: cd: ", path);
		perror(error_msg);
		free(error_msg);
	}
}
