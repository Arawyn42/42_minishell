/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_is_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:10:52 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 17:21:07 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_error_is_file2(struct dirent *dr, char *name, char *dir_name)
{
	char	*dir_n;

	if (dr->d_type == 4 && !ft_strncmp(name, dr->d_name,
			ft_strlen(dr->d_name)))
	{
		dir_n = ft_strjoin(dir_name, "/");
		free(dir_name);
		dir_name = ft_strjoin(dir_n, dr->d_name);
		free(dir_n);
		return (exec_error_is_file(name + ft_strlen(dr->d_name) + 1,
				dir_name));
	}
	if (!ft_strncmp(name, dr->d_name, ft_strlen(name)))
		return (free(dir_name), 1);
	return (0);
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
		if (exec_error_is_file2(dr, name, dir_name))
			return (closedir(dir), free(name), 1);
		dr = readdir(dir);
	}
	return (closedir(dir), free(name), free(dir_name), 0);
}
