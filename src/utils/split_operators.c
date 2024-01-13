/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:10:27 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/13 16:01:53 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_next_operator_pos(char *str, int *pos)
{
	while (str[++(*pos)])
	{
		if (ft_strncmp(&str[*pos], ">>", 2) == 0 || 
			ft_strncmp(&str[*pos], "<<", 2) == 0)
		{
			(*pos)++;
			return ;
		}
		else if (str[*pos] == '>' || str[*pos] == '<' || str[*pos] == '|')
			return ;
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
	int size;

	pos = -1;
	get_next_operator_pos(str, &pos);
	size = 0;
	while (pos != -1)
	{
		get_next_operator_pos(str, &pos);
		size++;
	}
	return (size);
}

char	**get_operators_array(char *str)
{
	char	**operators;
	int		pos;
	int		i;

	str = ft_strclean(str, " ");
	operators = malloc(sizeof(char *) * (operator_array_size(str) + 1));
	pos = -1;
	get_next_operator_pos(str, &pos);
	i = 0;
	while (pos != -1)
	{
		operators[i] = get_operator(str, pos);
		if (!operators[i])
		{
			free_double_array(operators);
			ft_putstr("minishell: syntax error: ", 2);
			ft_putstr("unexpected pipe or redirection\n", 2);
			return (free(str), NULL);
		}
		get_next_operator_pos(str, &pos);
		i++;
	}
	operators[i] = NULL;
	return (free(str), operators);
}
