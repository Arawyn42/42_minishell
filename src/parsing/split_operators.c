/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:10:27 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 19:26:42 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Returns the size of the next word found in line starting by i.
 *	If is_file == 1 aka the last word was one of the operators following : 
 *	>, <, >> and <<. Then the next word cannot contain spaces.
*/
static int	get_next_word_size(char *line, int i, int is_file)
{
	int	size;

	size = 0;
	while (line[i + size] && is_file && line[i + size] == ' ')
		size++;
	while (line[i + size] && \
		(is_in_quote(line, i + size) || (!ft_strchr("><|", line[i + size]) && \
		(!is_file || line[i + size] != ' '))))
		size++;
	return (size);
}

/*
 *	Returns the number of words it will be in the final split.
*/
static int	count_words(char *line)
{
	int	counter;
	int	is_file;

	counter = 0;
	is_file = 0;
	while (*line)
	{
		if (!ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
		{
			line++;
			counter++;
		}
		else if (*line == '>' || *line == '<' || *line == '|')
			counter++;
		if (*line == '>' || *line == '<')
			is_file = 1;
		if (*line != ' ' && *line != '>' && *line != '<' && *line != '|')
		{
			counter++;
			line += get_next_word_size(line, 0, is_file) - 1;
			is_file = 0;
		}
		line++;
	}
	return (counter);
}

/*
 *	Search for the next word found in the string line starting by the pos i
 *	then returns it.
 *	Returns NULL if the index i point to a space.
*/
static char	*get_word(char *line, int *i, int is_file)
{
	int	word_size;

	if (!ft_strncmp(&line[*i], "<<<", 3))
	{
		(*i) += 2;
		return (ft_strdup("<<<"));
	}
	else if (!ft_strncmp(&line[*i], ">>", 2) || !ft_strncmp(&line[*i], "<<", 2))
	{
		(*i)++;
		return (ft_substr(line, *i - 1, 2));
	}
	else if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
		return (ft_substr(line, *i, 1));
	else if (line[*i] != ' ')
	{
		word_size = get_next_word_size(line, *i, is_file);
		*i = *i + word_size - 1;
		return (ft_substr(line, *i - word_size + 1, word_size));
	}
	return (NULL);
}

/*
 *	Split the commands and the operators around the operators >, >>, <, << and |
 *	then returns the result.
 *	Note : The first string of the array is always NULL.
*/
char	**split_command(char *line)
{
	int		i;
	int		j;
	int		size;
	char	*word;
	char	**res;

	if (!line)
		return (NULL);
	size = count_words(line);
	res = malloc(sizeof(char *) * (size + 2));
	res[0] = NULL;
	j = 1;
	i = -1;
	while (line[++i])
	{
		word = get_word(line, &i, \
			(j > 1 && (res[j - 1][0] == '<' || res[j - 1][0] == '>')));
		if (word)
			res[j++] = word;
	}
	res[j] = NULL;
	free(line);
	return (res);
}
