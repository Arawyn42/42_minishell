/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:57 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 17:12:00 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	Ft_split modifications for Pipex:
 *	Ft_split no longer cut the string s when the separator c is found
 *	within simple quotes
 *	This is needed for some special case of Pipex like:
 *		./pipex infile cat "tr ' ' '.'" outfile
 *	In this example we want ft_split to keep the space inside 
 *	the simple quotes.
*/

#include "minishell.h"

/* Counts the number of words in a string according to a char-set */
static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	in_word;
	int	quotes[2];
	int	i;

	count = 0;
	in_word = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (s[i])
	{
		in_or_out_quotes(s, &quotes[0], &quotes[1], i);
		if (s[i] == c && !quotes[0] && !quotes[1])
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_word_dup2(const char *src, char c, int len)
{
	int		in_singleq;
	int		in_doubleq;
	int		quotes;
	int		i;
	char	*word;

	in_singleq = 0;
	in_doubleq = 0;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = -1;
	while (src[++i])
	{
		quotes = 0;
		in_or_out_quotes(src, &in_singleq, &in_doubleq, i);
		if (in_singleq || in_doubleq)
			quotes = 1;
		if (src[i] == c && !quotes)
			break ;
		word[i] = src[i];
	}
	word[i] = '\0';
	return (word);
}

/* Gets and dupplicate the first word of a string */
static char	*ft_word_dup(const char *src, char c)
{
	int	in_singleq;
	int	in_doubleq;
	int	quotes;
	int	len;

	in_singleq = 0;
	in_doubleq = 0;
	len = 0;
	while (src[len])
	{
		quotes = 0;
		in_or_out_quotes(src, &in_singleq, &in_doubleq, len);
		if (in_singleq || in_doubleq)
			quotes = 1;
		if (src[len] == c && !quotes)
			break ;
		len++;
	}
	return (ft_word_dup2(src, c, len));
}

static char	*ft_create_words(const char **s, char c, int *quotes)
{
	int		j;
	char	*res;

	j = 0;
	in_or_out_quotes((*s), &quotes[0], &quotes[1], j);
	while ((*s)[j] == c && !quotes[0] && !quotes[1])
		j++;
	res = ft_word_dup(&(*s[j]), c);
	if (!res)
		return (NULL);
	return (res);
}

/* Split a string into a strings array */
char	**ft_split(const char *s, char c)
{
	char	**res;
	int		word_count;
	int		i;
	int		quotes[2];

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (i < word_count)
	{
		res[i] = ft_create_words(&s, c, quotes);
		if (!res[i])
			return (free_double_array(res), NULL);
		s += ft_strlen(res[i]) + 1;
		i++;
	}
	res[i] = NULL;
	return (res);
}
