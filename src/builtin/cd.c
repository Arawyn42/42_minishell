/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 19:42:38 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_data *data)
{
	char	*error_msg;
	char	*path;

	parse_line(data);
	path = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
	if (chdir(path) == -1)
	{
		error_msg = ft_strjoin("minishell: cd: ", path);
		perror(error_msg);
		free(error_msg);
	}
}
