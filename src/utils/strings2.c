/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotine <nikotine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:15:29 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/04 12:53:24 by nikotine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char const *s, int c)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if (!(char) c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strdup(char const *src)
{
	int		i;
	char	*dest;

	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	count_double_quotes(char *str)
{
	int	i;
	int	double_quotes;

	i = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == 34)
			double_quotes++;
		i++;
	}
	return (double_quotes);
}

int	count_single_quotes(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == 39)
			quotes++;
		i++;
	}
	return (quotes);
}