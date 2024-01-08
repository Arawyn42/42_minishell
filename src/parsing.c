/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/08 19:44:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 *	Returns the index of the next minishell's operator in the string,
 *	returns -1 if no operator is found.
*/
int	get_operator(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|' || \
			str[i] == '>' || \
			str[i] == '<')
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
void	apply_next_operator(char *command1, char *command2, char *operator)
{
	(void)command1;
	(void)command2;
	if (!operator)
		return ;
	if (ft_strncmp(operator, "|", 1) == 0)
		printf("not supported yet\n");
	else if (ft_strncmp(operator, ">>", 2) == 0)
		printf("not supported yet\n");
	else if (ft_strncmp(operator, "<<", 2) == 0)
		printf("not supported yet\n");
	else if (ft_strncmp(operator, ">", 1) == 0)
		printf("not supported yet\n");
	else if (ft_strncmp(operator, "<", 1) == 0)
		printf("not supported yet\n");
	else
		printf("Error operator\n");
}

/*	WORK IN PROGRESS
 *	Parses the line by cutting the commands from the operators then
 *	run the commands.
*/
void input_handler(t_data *data)
{
	char	**commands;
	char 	*line;
	int		ope_pos;
	int		i;

	line = data->line;
	commands = ft_split(line, "|><");
	ope_pos = get_operator(line);
	i = -1;
	while (commands[++i + 1] && ope_pos != -1)
	{
		apply_next_operator(commands[i], commands[i + 1], &line[ope_pos]);
		line += ope_pos;
		ope_pos = get_operator(line);
	}
	if (i == 0)
	{
		free(data->line);
		data->line = ft_strdup(commands[i]);
		command_launcher(data);
	}
	free_double_array(commands);
}
