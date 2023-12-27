/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:57 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/26 20:56:36 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Counts the number of words in a string according to a char-set */
static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	in_word;
	int	quotes;

	count = 0;
	in_word = 0;
	quotes = 0;
	while (*s)
	{
		ft_quotes(*s, &quotes);
		if (quotes == 0)
		{
			if (*s == c)
				in_word = 0;
			else if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static char	*ft_word_dup2(const char *src, char c, int *quotes, int len)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (*src)
	{
		if (ft_quotes(*src, quotes) == 1)
			word[i++] = *src++;
		else if (*src != c)
			word[i++] = *src++;
		else
			break ;
	}
	word[i] = '\0';
	return (word);
}

/* Gets and dupplicate the first word of a string */
static char	*ft_word_dup(const char *src, char c, int *quotes)
{
	int		len;

	len = 0;
	while (src[len])
	{
		if (ft_quotes(src[len], quotes) == 1)
			len++;
		else if (src[len] != c)
			len++;
		else
			break ;
	}
	return (ft_word_dup2(src, c, quotes, len));
}

/* Frees the double array 'words' */
static void	ft_free_words(char **words, int count)
{
	while (count >= 0)
	{
		free(words[count]);
		count--;
	}
	free(words);
}

/* Split a string into a strings array */
char	**ft_split(const char *s, char c)
{
	char	**res;
	int		word_count;
	int		i;
	int		quotes;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	quotes = 0;
	while (i < word_count)
	{
		while (*s == c && ft_quotes(*s, &quotes) == 0)
			s++;
		res[i] = ft_word_dup(s, c, &quotes);
		if (!res[i])
			return (ft_free_words(res, i - 1), NULL);
		s += ft_strlen(res[i++]);
	}
	res[i] = NULL;
	return (res);
}
