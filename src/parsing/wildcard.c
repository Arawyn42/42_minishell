/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:31:49 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:56:28 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_start_path(char *line, int *i)
{
	int		j;
	char	*start_path;

	j = *i;
	while (j > 0 && line[j] != ' ')
		j--;
	j++;
	start_path = ft_substr(line, j, *i - j);
	return (start_path);
}

static int	start_path_cond(char *start_path, char *end_path,
				int slash, struct dirent *dr)
{
	if (ft_strncmp(dr->d_name, ".", 1) && ((!slash
				&& !ft_strncmp(dr->d_name + ft_strlen(dr->d_name)
					- ft_strlen(end_path), end_path, ft_strlen(end_path)))
			|| slash)
		&& !ft_strncmp(start_path, dr->d_name, ft_strlen(start_path)))
		return (1);
	else
		return (0);
}

char	*get_full_start_path(char *start_path, char *end_path, int slash)
{
	DIR				*dir;
	struct dirent	*dr;
	char			*full_path;
	char			*tmp;

	full_path = NULL;
	tmp = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	dr = readdir(dir);
	while (dr)
	{
		if (start_path_cond(start_path, end_path, slash, dr))
		{
			if (full_path)
				tmp = ft_strjoin(full_path, " ");
			free(full_path);
			full_path = ft_strjoin(tmp, dr->d_name);
			free(tmp);
		}
		dr = readdir(dir);
	}
	return (closedir(dir), full_path);
}

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
