/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/12 22:00:15 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_operator_pos(char *str, int *pos)
{
	while (str[++(*pos)])
	{
		if (str[*pos] == '|' || \
			str[*pos] == '>' || \
			str[*pos] == '<')
			return ;
	}
	*pos = -1;
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
	(void)file;
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
	int		operator_pos;
	int		i;

	line_backup = ft_strdup(data->line);
	cmds = ft_split(data->line, "|><");
	operator_pos = 0;
	get_operator_pos(line_backup, &operator_pos);
	i = -1;
	while (cmds[++i])
	{
		free(data->line);
		data->line = cmds[i];
		if (operator_pos == -1)
			free(line_backup), apply_next_operator(data, cmds[i + 1], NULL);
		else
		{
			apply_next_operator(data, cmds[i + 1], &line_backup[operator_pos]);
			get_operator_pos(line_backup, &operator_pos);
		}
	}
	free(cmds);
}
