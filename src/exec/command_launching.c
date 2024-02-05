/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:43:18 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 13:49:59 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launcher(char *command, t_data *data)
{
	char	*cmd;

	cmd = parse_line(ft_strdup(command), data->env, 1);
	if (!ft_strncmp(cmd, "pwd", 3) && (command[3] == ' ' || !command[3]))
		ft_pwd();
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
// void	apply_operator(t_data *data, int *i)
// {
// 	if (!data->command[*i + 1])
// 	{
// 		if (!builtin_launcher(data->command[*i], data))
// 			ft_fork_exec(data->command[*i], data);
// 	}
// 	else if (!ft_strncmp(data->command[*i], "|", 1))
// 		ft_pipe(data, i);
// 	else if (!ft_strncmp(data->command[*i], ">>", 2))
// 		output_redirection(data, i);
// 	else if (!ft_strncmp(data->command[*i], "<<", 2))
// 		here_doc(data, i);
// 	else if (!ft_strncmp(data->command[*i], ">", 1))
// 		output_redirection(data, i);
// 	else if (ft_strncmp(data->command[*i], "<", 1) == 0)
// 		input_redirection(data, i);
// }

static void	manage_redirections(t_data *data, int start)
{
	int	i;

	i = 0;
	while (data->command[start + i] && data->command[start + i][0] != '|')
	{
		if (!ft_strncmp(data->command[start + i], ">>", 2))
			data->output = output_redirection(data->command[start + i + 1],
				O_WRONLY | O_APPEND | O_CREAT);
		else if (!ft_strncmp(data->command[start + i], "<<", 2))
			data->input = here_doc(data->command[start + i + 1], data);
		else if (!ft_strncmp(data->command[start + i], ">", 1))
			data->output = output_redirection(data->command[start + i + 1],
				O_WRONLY | O_TRUNC | O_CREAT);
		else if (ft_strncmp(data->command[start + i], "<", 1) == 0)
			data->input = input_redirection(data->command[start + i + 1]);
		if (data->input == -1 || data->output == -1)
			break ;
		i++;
	}
}

static void	get_command_pos(char **command, int *pos)
{
	(*pos)++;
	while (command[*pos])
	{
		if (!ft_strchr("><|", command[*pos][0]) && \
			(*pos <= 0 || !is_file(command, *pos)))
			return ;
		(*pos)++;
	}
	*pos = -1;
	return ;
}

void	command_launcher(t_data *data)
{
	int	i;
	int	command_pos;
	int	saved_stdout;
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	data->input = 0;
	data->output = 1;
	command_pos = 0;
	i = 1;
	while (data->command[i])
	{
		manage_redirections(data, i);
		get_command_pos(data->command, &command_pos);
		while (data->command[i] && data->command[i][0] != '|')
			i++;
		if (data->command[i] && data->command[i][0] == '|')
		{
			ft_pipe(command_pos, data);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		if (data->command[i])
			i++;
	}
	if (command_pos != -1 && !is_file(data->command, command_pos) && data->output != -1 && data->input != -1)
	{
		if (!builtin_launcher(data->command[command_pos], data))
			ft_fork_exec(data->command[command_pos], data);
	}
	else
		g_exit_status = 1;
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
}
