/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/05 22:24:49 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(t_data *data)
{
	if (count_double_quotes(data->line) % 2
		|| count_single_quotes(data->line) % 2)
	{
		ft_putstr("minishell: cd: quotes error\n", 2);
		return (1);
	}
	if (data->line[2] && data->line[2] != ' ')
	{
		ft_exec(data->line, data->env);
		return (1);
	}
	return (0);
}

static char	*cd_home_path(t_data *data)
{
	char	*home_path;
	int		i;

	home_path = NULL;
	i = 0;
	while (data->env[i])
	{
		if (!strncmp(data->env[i], "HOME", 4))
			home_path = ft_substr(data->env[i], 5, ft_strlen(data->env[i]) - 5);
		i++;
	}
	return (home_path);
}

void	cd(t_data *data)
{
	char	*error_msg;
	char	*path;

	path = NULL;
	if (cd_error(data))
		return ;
	parse_line(data);
	if (!data->line[2])
		path = cd_home_path(data);
	else
		path = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
	if (chdir(path) == -1)
	{
		error_msg = ft_strjoin("minishell: cd: ", path);
		perror(error_msg);
		free(error_msg);
	}
}
