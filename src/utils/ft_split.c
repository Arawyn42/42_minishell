/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:57 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 17:46:27 by drenassi         ###   ########.fr       */
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

#include <stdio.h>
#include "minishell.h"

/*
 *	Counts the number of words containeds in a string
 *	and separated by a charset.
*/
static int	count_words(char const *s, char *charset)
{
	int	counter;
	int	in_word;
	int	in_quote;

	counter = 0;
	in_word = 0;
	in_quote = 0;
	while (*s)
	{
		if (ft_strchr(charset, *s) || ft_quote(&in_quote, *s))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			counter++;
		}
		s++;
	}
	return (counter);
}

/*
 *	Frees a double array of characters.
*/
static void	ft_free_split(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

/*
 *	Returns the next word according to a charset for the ft_split function.
*/
static char	*get_word(char const *s, char *charset, int *in_quote)
{
	int		size;
	char	*word;

	size = 0;
	while (s[size] && (ft_quote(in_quote, s[size]) || \
			!ft_strchr(charset, s[size])))
		size++;
	if (size == 0)
		return (NULL);
	word = ft_substr(s, 0, size);
	if (!word)
		return (NULL);
	return (word);
}

/*
 *	Splits a string into a strings array, according to a charset.
*/
char	**ft_split(char const *s, char *charset)
{
	char	**tab;
	int		in_quote;
	int		i;

	if (!s)
		return (NULL);
	in_quote = 0; // unclosed quote ?
	tab = (char **) ft_calloc(sizeof(char *), count_words(s, charset) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (ft_strchr(charset, *s) || ft_quote(&in_quote, *s)))
			s++;
		if (*s != '\0')
		{
			tab[i] = get_word(s, charset, &in_quote);
			if (!tab[i])
				return (ft_free_split(tab, i), NULL);
			s += ft_strlen(tab[i++]);
		}
	}
	tab[i] = NULL;
	return (tab);
}
