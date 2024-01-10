/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/10 23:44:37 by nsalles          ###   ########.fr       */
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
 *	Execute the command cmd in the environement env with the given operator.
 *	Operators list : 
 *		|	: pipe
 *		>	: output redirection
 *		<	: input redirection
 *		>>	: output redirection in append mode
 *		<<	: here_doc
 *	ARGUMENTS:
 *		char *cmd		: The command to execute.
 *		char *file		: NOT IMPLEMENTED.
 *		char *operator	: The operator.
 *		char **env		: The environement.
 *	RETURN VALUE:
 *		None.
*/
void	apply_next_operator(t_data *data, char *file, char *operator)
{
	(void)file;
	// write(2, "operator = ", 11);
	// write(2, operator, ft_strlen(operator));
	// write(2, "\n", 1);
	if (!operator)
		return ;
	if (ft_strncmp(operator, "|", 1) == 0)
		ft_pipe(data);
	else if (ft_strncmp(operator, ">>", 2) == 0)
		printf(">> is not supported yet\n");
	else if (ft_strncmp(operator, "<<", 2) == 0)
		printf("<< is not supported yet\n");
	else if (ft_strncmp(operator, ">", 1) == 0)
		printf("> is not supported yet\n");
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
	char	*line_backup;
	int		ope_pos;
	int		i;

	line_backup = ft_strdup(data->line);
	cmds = ft_split(data->line, "|><");
	ope_pos = 0;
	ope_pos = get_operator(line_backup);
	free(data->line);
	i = -1;
	while (cmds[++i + 1])
	{
		data->line = cmds[i];
		apply_next_operator(data, NULL, &line_backup[ope_pos]);
		ope_pos = get_operator(line_backup);
	}
	data->line = ft_strdup(cmds[i]);
	if (!command_launcher(data))
		ft_fork_exec(data->line, data->env);
	free_double_array(cmds);
	free(data->line);
	free(line_backup);
}
