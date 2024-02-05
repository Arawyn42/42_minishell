/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 17:52:36 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_command(char *str, int str_len, int *start)
{
	static char	*last_operator = NULL;
	int			len;
	char		*res;
	int			is_found;

	res = NULL;
	if (*start == -1 || str == NULL)
		return (NULL);
	len = -1;
	while (*start + ++len < str_len)
	{
		is_found = is_operator_found(str, &last_operator, start, len);
		if (is_found > 0)
			return (ft_substr(str, *start - len - 2, len));
		else if (is_found == -1)
			return (NULL);
		if (!logic_operator_condition(last_operator) && \
			str[*start + len] == '(')
			*start = skip_parenthesis(str, *start + len + 1, &len);
	}
	if (logic_operator_condition(last_operator))
		res = ft_substr(str, *start, str_len - *start);
	last_operator = NULL;
	*start = -1;
	return (res);
}

/*
 *	If there is two operators next to each other, prints an error and returns 0.
*/
int	is_command_valid(char **command)
{
	int	i;

	if (!command)
		return (0);
	if (command[1][0] == '|')
		return (syntax_error_message("|", 1), 0);
	i = 0;
	while (command[++i])
	{
		if (!ft_strncmp(command[i], "<<<", 3))
			return (ft_putstr("minishell: `<<<' is not supported\n", 2), 0);
		if (command[i + 1] && ft_strchr("><|", command[i][0]) && \
			ft_strchr("><|", command[i + 1][0]))
			return (syntax_error_message(command[i + 1], 2), 0);
	}
	if (ft_strchr("><", command[i - 1][0]))
		return (syntax_error_message("newline", 7), 0);
	if (command[i - 1][0] == '|')
		return (ft_putstr("minishell: here doc after pipe", 2), \
			ft_putstr(" is not supported (yet?)\n", 2), 0);
	return (1);
}

void	parse_and_launch(t_data *data)
{
	char	*tmp;
	int		line_len;
	int		i;

	tmp = ft_strtrim(data->line, " ");
	free(data->line);
	data->line = tmp;
	i = 0;
	line_len = ft_strlen(data->line);
	if (line_len == 0 || is_open_parentheses(data->line) || \
		is_logic_operators_broken(data->line))
		return ;
	data->command = parse_command(split_command(\
		get_command(data->line, line_len, &i)), data->env);
	while (is_command_valid(data->command))
	{
		data->input = 0;
		data->output = 1;
		command_launcher(data, dup(STDIN_FILENO), dup(STDOUT_FILENO));
		free_command(data->command);
		data->command = parse_command(split_command(\
			get_command(data->line, line_len, &i)), data->env);
	}
	if (data->command)
		free_command(data->command);
}
