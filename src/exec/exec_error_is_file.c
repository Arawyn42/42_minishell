/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_is_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:10:52 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 03:45:05 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	freenull(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

static int	exec_error_is_file2(struct dirent *dr, char *name, char *dir_name)
{
	char	*dir_n;

	if (!ft_strncmp(name, dr->d_name, ft_strlen(name)))
		return (free(dir_name), 1);
	if (dir_name && dr->d_type == 4
		&& !ft_strncmp(name, dr->d_name, ft_strlen(dr->d_name)))
	{
		dir_n = ft_strjoin(dir_name, "/");
		freenull(dir_name);
		dir_name = ft_strjoin(dir_n, dr->d_name);
		free(dir_n);
		return (exec_error_is_file(name + ft_strlen(dr->d_name) + 1,
				dir_name));
	}
	return (free(dir_name), 0);
}

int	exec_error_is_file(char *cmd, char *dir_name)
{
	char			*name;
	DIR				*dir;
	struct dirent	*dr;

	if (cmd[0] == '.' && cmd[1] == '/' && cmd[ft_strlen(cmd) - 1] == '/')
		name = ft_substr(cmd, 2, ft_strlen(cmd) - 3);
	else if (cmd[0] == '.' && cmd[1] == '/' && cmd[ft_strlen(cmd) - 1] != '/')
		name = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
	else
		name = ft_strdup(cmd);
	dir = opendir(dir_name);
	dr = readdir(dir);
	while (dr)
	{
		if (exec_error_is_file2(dr, name, ft_strdup(dir_name)))
			return (closedir(dir), free(name), free(dir_name), 1);
		dr = readdir(dir);
	}
	return (closedir(dir), free(name), free(dir_name), 0);
}
