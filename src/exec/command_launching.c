/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:43:18 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/06 14:27:28 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Search if the command given in parameter is a builtin. If yes, execute it
 *	and returns 0, if no return 1.
*/
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
 *	Search in data->command between the start index and the next pipe (or
 *	NULL) for all the redirections, then create all the files and setup the
 *	standard input / standard output on this files.
*/
static void	manage_redirections(t_data *data, int start, int saved_stdin)
{
	int	i;

	i = 0;
	while (data->command[start + i] && data->command[start + i][0] != '|')
	{
		if (!ft_strncmp(data->command[start + i], ">>", 2))
			data->output = output_redirection(data->command[start + i + 1],
					O_WRONLY | O_APPEND | O_CREAT, data->env);
		else if (!ft_strncmp(data->command[start + i], "<<", 2))
			data->input = here_doc(data->command[start + i + 1], data, \
				saved_stdin);
		else if (!ft_strncmp(data->command[start + i], ">", 1))
			data->output = output_redirection(data->command[start + i + 1],
					O_WRONLY | O_TRUNC | O_CREAT, data->env);
		else if (ft_strncmp(data->command[start + i], "<", 1) == 0)
			data->input = input_redirection(data->command[start + i + 1], \
				data->env);
		if (data->input == -1 || data->output == -1)
			break ;
		i++;
	}
}

/*
 *	Search from the position pos in the array for the next command.
 *	Set the value pointed by pos to the index of the command found in the array.
*/
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

/*
 *	Launch the last command found in data->command, the position of this command
 *	should be given.
*/
static void	launch_last_command(t_data *data, int command_pos)
{
	if (command_pos != -1 && !is_file(data->command, command_pos) \
		&& data->output != -1 && data->input != -1)
	{
		if (!builtin_launcher(data->command[command_pos], data))
			ft_fork_exec(data->command[command_pos], data);
	}
	else if (ft_strlen(data->command[1]) && \
		(data->output == -1 || data->input == -1))
		g_exit_status = 1;
}

/*
 *	Manage all the redirections and execute the commands found in data->command.
 *	Requieres backup of STDOUT and STDIN streams
*/
void	command_launcher(t_data *data, int saved_stdin, int saved_stdout)
{
	int	i;
	int	command_pos;

	command_pos = 0;
	i = 1;
	while (data->command[i])
	{
		manage_redirections(data, i, saved_stdin);
		get_command_pos(data->command, &command_pos);
		while (data->command[i] && data->command[i][0] != '|')
			i++;
		if (data->command[i] && data->command[i][0] == '|')
		{
			ft_pipe(command_pos, data);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		i += data->command[i] != 0;
	}
	launch_last_command(data, command_pos);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
}
