/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/16 19:52:22 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	error_value;

static int	cd_error(t_data *data)
{
	if (data->line[2] && data->line[2] != ' ')
	{
		ft_exec(data->line, data->env);
		return (1);
	}
	return (0);
}

static int	cd_check_args(t_data *data)
{
	int	i;

	i = 3;
	while (data->line[2] && data->line[i])
	{
		if (data->line[i] == ' ')
		{
			ft_putstr("minishell: cd: too many arguments\n", 2);
			error_value = 1;
			return (0);
		}
		i++;
	}
	return (1);
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

void	ft_cd(t_data *data)
{
	char	*error_msg;
	char	*path;

	path = NULL;
	if (cd_error(data))
		return ;
	if (!cd_check_args(data))
		return ;
	if (!data->line[2])
		path = cd_home_path(data);
	else if (!ft_strcmp(data->line, "cd -"))
		path = get_oldpwd(data);
	else
		path = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
	set_old_pwd(data);
	error_value = 0;
	if (chdir(path) == -1)
	{
		error_msg = ft_strjoin("minishell: cd: ", path);
		perror(error_msg);
		error_value = 1;
		free(error_msg);
	}
	set_pwd(data);
	free(path);
}
