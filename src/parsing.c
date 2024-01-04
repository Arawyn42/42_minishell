/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotine <nikotine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nikotine          #+#    #+#             */
/*   Updated: 2024/01/04 12:43:50 by nikotine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 *	Returns the index of the next minishell's operator in the string,
 *	returns -1 if no operator is found.
*/
int	operator_pos(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (i);
	return (-1);
}

/*
 *	Applies the next operator found in the command line
 *	operator list : 
 *		|	: pipe
 *		>	: output redirection
 *		<	: input redirection
 *		>>	: output redirection in append mode
 *		<<	: here_doc
*/
void	apply_next_operator(char *line)
{
	int 	pos;
	pid_t	pid;

	pos = operator_pos(line);
	if (pos == -1)
		return ;
	pid = fork();
	if (pid == 0)
		return ;
	if (line[pos] == '|')
		printf("not supported yet\n");
		// ft_pipe(line, pos);
	if (line[pos] == '>' && line[pos + 1] != '>')
		printf("not supported yet\n");
	if (line[pos] == '<' && line[pos + 1] != '<')
		printf("not supported yet\n");
	if (line[pos] == '>' && line[pos + 1] == '>')
		printf("not supported yet\n");
	if (line[pos] == '<' && line[pos + 1] == '<')
		printf("not supported yet\n");
	printf("Error operator\n");
	exit(EXIT_FAILURE);
}

/*	WORK IN PROGRESS
 *	Parses the line by cutting the commands from the operators then
 *	run the commands.
*/
void input_handler(t_data *data)
{
	char	*line;
	int		pos;

	line = ft_strdup(data->line);
	pos = operator_pos(line);
	while (pos != -1)
	{
		free(data->line);
		data->line = ft_substr(line, 0, pos);
		command_launcher(data);
		line += pos;
		pos = operator_pos(line);
	}
	free(data->line);
	data->line = line;
	command_launcher(data);
}


// int	parsed_line_len(char *line)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'' || line[i] == '\"')
// 		{

// 		}
// 		i++;
// 	}
// }

// char	*parse_line(char *line)
// {
// 	int		i;
// 	char	*new_line;
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	new_line = 
// 	while (line[i])
// 	{
		

// 	}
// 	free(line);
// 	return (new_line);
// }
