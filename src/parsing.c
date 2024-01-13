/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/13 16:09:21 by nsalles          ###   ########.fr       */
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
	char	**cmds;
	char	**operators;
	int		i;

	operators = get_operators_array(data->line);
	if (!operators)
		return ;
	cmds = ft_split(data->line, "|><");
	i = -1;
	while (cmds[++i])
	{
		free(data->line);
		data->line = cmds[i];
		apply_next_operator(data, cmds[i + 1], operators[i]);
	}
	free(cmds);
	free_double_array(operators);
}
