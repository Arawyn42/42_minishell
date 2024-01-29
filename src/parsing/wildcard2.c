/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:26:39 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/26 19:06:35 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wildcard_after_slash(char *line, char *end_path, int *i, int slash)
{
	char	*start_path;
	char	*path;
	char	*add_path;

	(*i)--;
	start_path = get_start_path(line, i);
	path = get_full_start_path(start_path, end_path, slash);
	add_path = NULL;
	if (path)
		add_path = get_slash_path(start_path, end_path);
	(*i)++;
	return (free(start_path), free(path), add_path);
}

static char	*wildcard_after_char(char *line, char *end_path, int *i, int slash)
{
	char	*start_path;
	char	*path;
	char	*add_path;

	start_path = get_start_path(line, i);
	add_path = get_full_start_path(start_path, end_path, slash);
	path = ft_substr(add_path, ft_strlen(start_path),
			ft_strlen(add_path) - ft_strlen(start_path));
	// printf("start_path: %s\nend_path: %s\npath: %s\n", start_path, end_path, path);
	return (free(start_path), free(add_path), path);
}

static char	*get_parsed_wildcard(char *line, int *i)
{
	char	*add_path;
	char	*path;
	char	*end_path;
	int		j;
	int		slash;

	add_path = NULL;
	j = 0;
	while (line[*i + j + 1] && line[*i + j + 1] != ' '
			&& line[*i + j + 1] != '/')
		j++;
	slash = 0;
	if (i > 0 && line[*i - 1] == '/')
		slash = 1;
	if (line[*i + j + 1] == '/')
		slash = 2;
	end_path = ft_substr(line, *i + 1, j);
	if (i > 0 && line[*i - 1] == '/')
		add_path = wildcard_after_slash(line, end_path, i, slash);
	else
		add_path = wildcard_after_char(line, end_path, i, slash);
	path = ft_substr(add_path, 0, ft_strlen(add_path) - ft_strlen(end_path));
	return (free(end_path), free(add_path), path);
}

void	parse_wildcard(char *line, char *new_line, int *i, int *j)
{
	char	*path;
	int		k;

	path = get_parsed_wildcard(line, i);
	if (!path || !path[0])
	{
		new_line[*j] = '*';
		(*j)++;
	}
	k = 0;
	while (path && path[k])
	{
		new_line[*j] = path[k];
		(*j)++;
		k++;
	}
	if (path)
		free(path);
}

void	wildcard_len(t_data *data, int *i, int *len)
{
	char	*path;

	path = get_parsed_wildcard(data->line, i);
	if (!path || !path[0])
		(*len)++;
	else
		(*len) += ft_strlen(path);
	if (path)
		free(path);
}
