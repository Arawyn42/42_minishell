/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:31:49 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/26 19:29:58 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_start_path(char *line, int *i)
{
	int		j;
	char	*start_path;

	j = *i;
	while (j > 0 && (line[j] != ' '))
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
			|| slash == 1 || (slash == 2 && dr->d_type == 4))
		&& !ft_strncmp(start_path, dr->d_name, ft_strlen(start_path)))
		return (1);
	else
		return (0);
}

static void	full_path_join(char **full_path, char **tmp,
				int slash, struct dirent *dr)
{
	if (*full_path)
		*tmp = ft_strjoin(*full_path, " ");
	if (*full_path && slash == 2)
	{
		free(*tmp);
		*tmp = ft_strjoin(*full_path, "/ ");
	}
	free(*full_path);
	*full_path = ft_strjoin(*tmp, dr->d_name);
	free(*tmp);
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
			full_path_join(&full_path, &tmp, slash, dr);
		dr = readdir(dir);
	}
	return (closedir(dir), full_path);
}
