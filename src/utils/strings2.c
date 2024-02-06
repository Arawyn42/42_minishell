/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:15:29 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 15:00:53 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Searches for an occurence of a character in a string.
*/
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

/*
 *	Duplicates a string and returns the duplicated string.
*/
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

/*
 *	Compares two strings on n characters. Returns 0 if there is no difference.
*/
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

/*
 *	Trims all characters from a charset presents at the beginning and at the end
 *	of a string and returns the result.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > 0 && ft_strchr(set, s1[j]))
		j--;
	res = ft_substr(s1, i, j - i + 1);
	return (res);
}

/*
 *	Search for the character at the position pos in the string str.
 *	Returns 1 if this character is in quotes, else returns 0.
*/
int	is_in_quote(char *str, int pos)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] == 39 && (i == 0 || str[i - 1] != 92))
			single_quote++;
		else if (str[i] == 34 && (i == 0 || str[i - 1] != 92) && \
				single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	return (double_quote % 2 == 1 || single_quote % 2 == 1);
}
