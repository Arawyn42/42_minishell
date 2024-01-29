/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:57:14 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 22:54:39 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Joins two strings into one, frees the first one and returns the result.
*/
static char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

/*
 *	Returns the new stash.
*/
static char	*ft_stash(char *stash)
{
	int		i;
	char	*res;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	res = ft_substr(stash, i, ft_strlen(stash) - i + 1);
	free(stash);
	if (res[0] == 0)
	{
		free(res);
		res = NULL;
	}
	return (res);
}

/*
 *	Returns the current line.
*/
static char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

/*
 *	Reads the fd and joins the buffer in the stash until a new line is found.
*/
static char	*ft_read(int fd, char *buffer, char *stash)
{
	int		r;

	r = 1;
	while (r && !ft_strchr(stash, '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (r == 0)
			break ;
		buffer[r] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

/*
 *	Returns the next line found in a file descriptor.
*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = ft_read(fd, buffer, stash);
	line = ft_get_line(stash);
	stash = ft_stash(stash);
	return (line);
}
