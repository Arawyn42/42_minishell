/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 01:08:40 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launcher(t_data *data)
{
	if (!data->line)
		return (1);
	if (!ft_strncmp(data->line, "pwd", 3)
		&& (data->line[3] == ' ' || !data->line[3]))
		ft_pwd();
	else if (!ft_strcmp(data->line, "echo")
		|| !ft_strncmp(data->line, "echo ", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->line, "cd", 2))
		ft_cd(data);
	else if (!ft_strcmp(data->line, "env")
		|| !ft_strncmp(data->line, "env ", 4))
		ft_print_env(data);
	else if (!ft_strcmp(data->line, "export")
		|| !ft_strncmp(data->line, "export ", 7))
		ft_export(data);
	else if (!ft_strcmp(data->line, "unset")
		|| !ft_strncmp(data->line, "unset ", 6))
		ft_unset(data);
	else
		return (0);
	return (1);
}

/*
 *	Execute the command cmd in the environement env with the given operator.
 *	Operators list : 
 *		|	: pipe
 *		>	: output redirection
 *		<	: input redirection
 *		>>	: appending redirected output
 *		<<	: here document
*/
void	apply_operator(char *operator, char **cmds, int *index, t_data *data)
{
	if (!operator)
	{
		data->line = parse_line(ft_strdup(cmds[*index]), data->env);
		if (!builtin_launcher(data))
			ft_fork_exec(data->line, data->env);
	}
	else if (ft_strncmp(operator, "|", 1) == 0)
		ft_pipe(cmds[*index], data);
	else if (ft_strncmp(operator, ">>", 2) == 0)
		output_redirection(cmds, index, O_WRONLY | O_APPEND | O_CREAT, data);
	else if (ft_strncmp(operator, "<<", 2) == 0)
		here_doc(cmds, index, data);
	else if (ft_strncmp(operator, ">", 1) == 0)
		output_redirection(cmds, index, O_WRONLY | O_TRUNC | O_CREAT, data);
	else if (ft_strncmp(operator, "<", 1) == 0)
		input_redirection(cmds, index, data);
}

/*	WORK IN PROGRESS
 *	Parses the line by cutting the commands from the operators then
 *	run the commands.
*/
// void input_handler(t_data *data)
// {
// 	char	**commands;
// 	char	**operators;
// 	int		i;
// 	int		j;

// 	operators = get_operators_array(data->line);
// 	if (!operators)
// 		return ;
// 	commands = ft_split(data->line, "|><");
// 	i = -1;
// 	j = 0;
// 	while (commands[++i])
// 	{
// 		free(data->line);
// 		data->line = parse_line(commands[i], data->env);
// 		if (operators[j] && commands[i + 1] && 
// 			ft_strchr("<>", operators[i][0]))
// 		{
// 			commands[i + 1] = parse_line(commands[i + 1], data->env);
// 			apply_operator(data, commands[i + 1], operators[j]);
// 			free(commands[++i]);
// 		}
// 		else
// 			apply_operator(data, NULL, operators[i]);
// 		j++;
// 	}
// 	free(commands);
// 	free_double_array(operators); // still reachable leaks with exit command
// }

/*
 *	Parses the line by cutting the commands from the operators then
 *	run the commands.
 *	Unlike bash, this implementation does not support any redirection or 
 *	pipe after an output redirection. (yet ?)
*/
void	command_launcher(t_data *data)
{
	char	**commands;
	char	**operators;
	int		saved_stdin;
	int		saved_stdout;
	int		i;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	operators = get_operators_array(data->line);
	if (!operators)
		return ;
	commands = ft_split(data->line, "|><");
	free(data->line);
	i = -1;
	while (commands[++i])
		apply_operator(operators[i], commands, &i, data);
	free_double_array(operators);
	free_double_array(commands);
	free(data->line);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);

}

