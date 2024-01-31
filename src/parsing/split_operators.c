/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:10:27 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/31 13:15:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *line)
{
	int	i;
	int	counter;

	counter = 0;
	i = -1;
	while (line[++i])
	{
		if (!ft_strncmp(&line[i], ">>", 2) || !ft_strncmp(&line[i], "<<", 2))
		{
			i++;
			counter++;
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			counter++;
		else if (line[i] != ' ')
		{
			counter++;
			while (line[i] && (is_in_quote(line, i) || \
				!ft_strchr("><|", line[i])))
				i++;
			i--;
		}
	}
	return (counter);
}

static char	*get_word(char *line, int *i)
{
	int	len;

	if (!ft_strncmp(&line[*i], "<<<", 3))
	{
		(*i) += 2;
		return (ft_substr(line, *i - 2, 3));
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
		len = 0;
		while (line[*i + len] && (is_in_quote(line, *i + len) || \
			!ft_strchr("><|", line[*i + len])))
			len++;
		*i = *i + len - 1;
		return (ft_substr(line, *i - len + 1, len));
	}
	return (NULL);
}

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
		word = get_word(line, &i);
		if (word)
			res[j++] = word;
	}
	res[j] = NULL;
	free(line);
	return (res);
}

/*
static void	get_next_operator_pos(char *str, int *pos, int *in_quote)
{
	while (str[++(*pos)])
	{
		if (!ft_quote(in_quote, str[(*pos)]))
		{
			if (ft_strncmp(&str[*pos], ">>", 2) == 0 || \
				ft_strncmp(&str[*pos], "<<", 2) == 0)
			{
				(*pos)++;
				return ;
			}
			else if (str[*pos] == '>' || str[*pos] == '<' || str[*pos] == '|')
				return ;
		}
	}
	*pos = -1;
}

static char	*get_operator(char *str, int pos)
{
	if (ft_strncmp(&str[pos], "|", 1) == 0 && \
		(!str[pos + 1] || !ft_strchr("|><", str[pos + 1])))
		return (ft_strdup("|"));
	if (pos && ft_strncmp(&str[pos - 1], ">>", 2) == 0 && \
		(!str[pos + 1] || !ft_strchr("|><", str[pos + 1])))
		return (ft_strdup(">>"));
	if (pos && ft_strncmp(&str[pos - 1], "<<", 2) == 0 && \
		(!str[pos + 1] || !ft_strchr("|><", str[pos + 1])))
		return (ft_strdup("<<"));
	if (ft_strncmp(&str[pos], ">", 1) == 0 && \
		(!str[pos + 1] || !ft_strchr("|><", str[pos + 1])))
		return (ft_strdup(">"));
	if (ft_strncmp(&str[pos], "<", 1) == 0 && \
		(!str[pos + 1] || !ft_strchr("|><", str[pos + 1])))
		return (ft_strdup("<"));
	return (NULL);
}

static int	operator_array_size(char *str)
{
	int	pos;
	int	size;
	int	in_quote;

	pos = -1;
	in_quote = 0;
	get_next_operator_pos(str, &pos, &in_quote);
	size = 0;
	while (pos != -1)
	{
		get_next_operator_pos(str, &pos, &in_quote);
		size++;
	}
	return (size);
}

char	**get_operators_array(char *str)
{
	char	**operators;
	int		pos;
	int		i;
	int		in_quote;

	in_quote = 0;
	str = ft_strclean(str, " ");
	operators = malloc(sizeof(char *) * (operator_array_size(str) + 1));
	pos = -1;
	get_next_operator_pos(str, &pos, &in_quote);
	i = 0;
	while (pos != -1)
	{
		operators[i] = get_operator(str, pos);
		if (!operators[i++])
		{
			free_double_array(operators);
			ft_putstr("minishell: syntax error: ", 2);
			ft_putstr("unexpected pipe or redirection\n", 2);
			return (free(str), NULL);
		}
		get_next_operator_pos(str, &pos, &in_quote);
	}
	operators[i] = NULL;
	return (free(str), operators);
}
*/