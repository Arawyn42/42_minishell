/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:57 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 16:30:29 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Ft_split modifications for Pipex:
*	Ft_split no longer cut the string s when the separator c is found
*	within simple quotes
*	This is needed for some special case of Pipex like:
*		./pipex infile cat "tr ' ' '.'" outfile
*	In this example we want ft_split to keep the space inside 
*	the simple quotes.
*/

#include <stdio.h>
#include "minishell.h"

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

static void	ft_free_split(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

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

char	**ft_split(char const *s, char *charset)
{
	char	**tab;
	int		in_quote;
	int		i;

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
