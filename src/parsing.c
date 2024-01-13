/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/13 20:59:17 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Execute the command cmd in the environement env with the given operator.
 *	Operators list : 
 *		|	: pipe
 *		>	: output redirection
 *		<	: input redirection
 *		>>	: output redirection in append mode
 *		<<	: here_doc
 *	ARGUMENTS:
 *		t_data	*data		: The main datastructure
 *		char	*file		: The file to open 
 *		char 	*operator	: The operator.
 *	RETURN VALUE:
 *		None.
*/
void	apply_next_operator(t_data *data, char *file, char *operator)
{
	// write(2, "operator = ", 11);
	// write(2, operator, ft_strlen(operator));
	// write(2, "\n", 1);
	if (!operator)
	{
		if (!command_launcher(data))
			ft_fork_exec(data->line, data->env);
	}
	else if (ft_strncmp(operator, "|", 1) == 0)
		ft_pipe(data);
	else if (ft_strncmp(operator, ">>", 2) == 0)
		printf(">> is not supported yet\n");
	else if (ft_strncmp(operator, "<<", 2) == 0)
		printf("<< is not supported yet\n");
	else if (ft_strncmp(operator, ">", 1) == 0)
		output_redirection(file, data);
	else if (ft_strncmp(operator, "<", 1) == 0)
		printf("< is not supported yet\n");
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
	char	**operators;
	int		i;
	int		j;

	operators = get_operators_array(data->line);
	if (!operators)
		return ;
	commands = ft_split(data->line, "|><");
	i = -1;
	j = 0;
	while (commands[++i])
	{
		free(data->line);
		data->line = parse_line(commands[i], data->env);
		if (operators[j] && commands[i + 1] && \
			ft_strchr("<>", operators[i][0]))
		{
			commands[i + 1] = parse_line(commands[i + 1], data->env);
			apply_next_operator(data, commands[i + 1], operators[j]);
			free(commands[++i]);
		}
		else
			apply_next_operator(data, NULL, operators[i]);
		j++;
	}
	free(commands);
	free_double_array(operators); // still reachable leaks with exit command
}
