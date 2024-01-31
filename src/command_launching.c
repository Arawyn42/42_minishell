/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:43:18 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/01 00:17:31 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launcher(char *command, t_data *data)
{
	char	*cmd;
	// if (!data->line)
		// return (1);

	cmd = parse_line(ft_strdup(command), data->env);
	if (!ft_strncmp(cmd, "pwd", 3) && (command[3] == ' ' || !command[3]))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd, "echo")
		|| !ft_strncmp(cmd, "echo ", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd, "cd", 2))
		ft_cd(cmd, data);
	else if (!ft_strcmp(cmd, "env")
		|| !ft_strncmp(cmd, "env ", 4))
		ft_print_env(cmd, data);
	else if (!ft_strcmp(cmd, "export")
		|| !ft_strncmp(cmd, "export ", 7))
		ft_export(cmd, data);
	else if (!ft_strcmp(cmd, "unset")
		|| !ft_strncmp(cmd, "unset ", 6))
		ft_unset(cmd, data);
	else if ((!ft_strcmp(cmd, "exit") || \
		!ft_strncmp(cmd, "exit ", 5)))
		ft_exit(cmd, data);
	else
		return (free(cmd), 0);
	return (free(cmd), 1);
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