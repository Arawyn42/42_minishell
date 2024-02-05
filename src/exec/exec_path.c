/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:26:45 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 18:55:46 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Search in the environnement for the variable named $PATH and returns
 *	it's content.
*/
char	*ft_get_path_env(char **env)
{
	int		i;
	int		j;
	char	*env_name;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		env_name = ft_substr(env[i], 0, j);
		if (!ft_strcmp(env_name, "PATH"))
		{
			free(env_name);
			return (&env[i][j + 1]);
		}
		free(env_name);
		i++;
	}
	return (NULL);
}

/*
 *	Search in the environnement for the variable named $PATH and returns
 *	the full path of the command given in parameter.
*/
char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*cmd_path;
	char	**path_array;
	char	*path_slash;

	i = 0;
	path_array = ft_split(ft_get_path_env(env), ':');
	while (path_array && path_array[i])
	{
		path_slash = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(path_slash, cmd);
		free(path_slash);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free_double_array(path_array);
	cmd_path = ft_strdup(cmd);
	return (cmd_path);
}

/*
 *	Does the same thing as ft_exec but does not exit the process.
*/
void	ft_fork_exec(char *cmds, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
		ft_exec(cmds, data);
	else
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
}

/*
 *	Search in $PATH of the environnement for the command given in parameter
 *	and execute it.
 *	If the command is not found, prints an error and setup the exit_status
 *	accordingly.
 *	Exit the process.
*/
void	ft_exec(char *command, t_data *data)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(command, ' ');
	cmd_path = ft_get_path(cmd[0], data->env);
	cmd = trim_command(cmd, "\'\"");
	if (execve(cmd_path, cmd, data->env) == -1)
	{
		exec_error(data, cmd, cmd_path);
		exit(g_exit_status);
	}
}
