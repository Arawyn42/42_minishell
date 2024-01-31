/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:43:18 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/31 13:55:45 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launcher(char *command, t_data *data)
{
	// if (!data->line)
		// return (1);
	if (!ft_strncmp(command, "pwd", 3)
		&& (command[3] == ' ' || !command[3]))
		ft_pwd();
	else if (!ft_strcmp(command, "echo")
		|| !ft_strncmp(command, "echo ", 5))
		ft_echo(command);
	else if (!ft_strncmp(command, "cd", 2))
		ft_cd(command, data);
	else if (!ft_strcmp(command, "env")
		|| !ft_strncmp(command, "env ", 4))
		ft_print_env(data);
	else if (!ft_strcmp(command, "export")
		|| !ft_strncmp(command, "export ", 7))
		ft_export(command, data);
	else if (!ft_strcmp(command, "unset")
		|| !ft_strncmp(command, "unset ", 6))
		ft_unset(command, data);
	else if ((!ft_strcmp(command, "exit") || \
		!ft_strncmp(command, "exit ", 5)))
		ft_exit(command, data);
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
void	apply_operator(t_data *data, int *i)
{
	if (!data->command[*i + 1])
	{
		if (!builtin_launcher(data->command[*i], data))
			ft_fork_exec(data->command[*i], data);
	}
	else if (!ft_strncmp(data->command[*i], "|", 1))
		ft_pipe(data, i);
	else if (!ft_strncmp(data->command[*i], ">>", 2))
		output_redirection(data, i, O_WRONLY | O_APPEND | O_CREAT);
	else if (!ft_strncmp(data->command[*i], "<<", 2))
		here_doc(data, i);
	else if (!ft_strncmp(data->command[*i], ">", 1))
		output_redirection(data, i, O_WRONLY | O_TRUNC | O_CREAT);
	else if (ft_strncmp(data->command[*i], "<", 1) == 0)
		input_redirection(data, i);
}

void	command_launcher(t_data *data)
{
	int			i;

	i = 0;
	while (data->command[++i])
		apply_operator(data, &i);  // fix `ls > file > file2 > file3`
}