/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_operators_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:33:20 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 23:04:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_logic_operators_broken(char *line)
{
	int	i;
	int	last_operator_pos;
	int	is_ok;
	int	len;

	len = ft_strlen(line);
	i = -1;
	last_operator_pos = 0;
	is_ok = 0;
	while (++i < len)
	{
		if (!ft_strncmp(&line[i], "&&", 2) || !ft_strncmp(&line[i], "||", 2))
		{
			if (!is_ok)
				return (syntax_error_message(&line[i], 2), 1);
			is_ok = 0;
			last_operator_pos = i;
			i += 2;
		}
		if (line[i] && !ft_strchr(" ()", line[i]))
			is_ok = 1;
	}
	if (!is_ok)
		return(syntax_error_message(&line[last_operator_pos], 2), 1);
	return (0);
}

int	is_open_parentheses(char *line)
{
	int		parentheses_depth; // toujours la flemme ? (commenté en bas)
	int		i;

	parentheses_depth = 0;
	i = -1;
	while (line[++i])
	{
		if (!is_in_quote(line, i))
			parentheses_depth += (line[i] == '(') - (line[i] == ')');
		if (parentheses_depth < 0)
		{
			syntax_error_message(")", 1);
			return (1);
		}
	}
	if (parentheses_depth > 0)
	{
		syntax_error_message("(", 1);
		return (1);
	}
	return (0);
}

// char	*logic_operator_here_doc(char *line, int *line_len)
// {
// 	char	*new_line;
// 	char	*user_input;

// 	if (*line_len > 2 && (!ft_strncmp(&line[*line_len - 2], "&&", 2) ||
// 			!ft_strncmp(&line[*line_len - 2], "||", 2)))
// 	{
// 		write(0, "> ", 2);
// 		user_input = get_next_line(0);
// 		new_line = ft_strjoin(line, user_input);
// 		*line_len = ft_strlen(new_line);
// 		new_line[--(*line_len)] = '\0';
// 		free(line);
// 		free(user_input);
// 		return (new_line);
// 	}
// 	return (line);
// }

// char	*logic_operator_parentheses(char *line, int *line_len)
// {
// 	char	*user_input;
// 	char	*new_line;
// 	int		parentheses_depth;
// 	int		i;

// 	parentheses_depth = 0;
// 	i = -1;
// 	while (line[++i])
// 		parentheses_depth += (line[i] == '(') - (line[i] == ')');
// 	new_line = ft_strdup(line);
// 	while (parentheses_depth > 0)
// 	{
// 		write(0, "> ", 2);
// 		printf("%d\n", parentheses_depth);
// 		user_input = get_next_line(0);
// 		if (!user_input)
// 			return (free(line), free(new_line), NULL);
// 		user_input[ft_strlen(user_input) - 1] = '\0';
// 		new_line = ft_strjoin(new_line, user_input);
// 		free(user_input);
// 		i = -1;
// 		parentheses_depth = 0;
// 		while (new_line[++i])
// 			parentheses_depth += (new_line[i] == '(') - (new_line[i] == ')');
// 	}
// 	if (parentheses_depth < 0)
// 		return (syntax_error_message(")"), free(line), free(new_line), NULL);
// 	*line_len = ft_strlen(new_line);
// 	return (free(line), new_line);
// }
