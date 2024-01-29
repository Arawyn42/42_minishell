/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:14:53 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/26 19:15:06 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_slash_path2(char *start_path, char **path, char **tmp)
{
	if (*path)
	{
		*tmp = ft_strjoin(*path, " ");
		free(*path);
		*path = ft_strjoin(*tmp, start_path);
		free(*tmp);
		*tmp = ft_strjoin(*path, "/");
		free(*path);
	}
}

char	*get_slash_path(char *start_path, char *end_path)
{
	DIR				*dir;
	struct dirent	*dr;
	char			*path;
	char			*tmp;

	path = NULL;
	tmp = NULL;
	dir = opendir(start_path);
	if (!dir)
		return (NULL);
	dr = readdir(dir);
	while (dr)
	{
		if (ft_strncmp(dr->d_name, ".", 1)
			&& !ft_strncmp(dr->d_name + ft_strlen(dr->d_name)
				- ft_strlen(end_path), end_path, ft_strlen(end_path)))
		{
			get_slash_path2(start_path, &path, &tmp);
			path = ft_strjoin(tmp, dr->d_name);
			free(tmp);
		}
		dr = readdir(dir);
	}
	return (closedir(dir), path);
}
