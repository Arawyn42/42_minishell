/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:26:45 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/11 17:25:17 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**************************** Open a file *******************************/
/* If it's on the standard input, opens it with READ ONLY.				*/
/* The 0777 argument is a chmod with full rights.						*/
/* If it's on the standard output (1), opens it with WRITE ONLY.		*/
/* If pathname doesn't exist, create it as a regular file (O_CREAT).	*/
/* If the file exists and the access mode allows writing, it will be	*/
/* truncated to length 0, which means empty the file before writting	*/
/* in it (O_TRUNC). For bonus, if we have a here_doc, the O_TRUNC		*/
/* parameter is replaced with O_APPEND so we append each line to the	*/
/* end file instead of empty it.										*/
/************************************************************************/
int	ft_open(char *file, int in_out)
{
	int	res;

	if (in_out == 0)
		res = open(file, O_RDONLY, 0666);
	if (in_out == 1)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (in_out == -1)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (res == -1)
		exit(127);
	return (res);
}

/******************** Get the environnement 'PATH' **********************/
/* For this, it checks each array in the char **env until we get the	*/
/* PATH line. Then, it returns a pointer on the first character after	*/
/* the "=" in "PATH=...".												*/
/************************************************************************/
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

/************ Get the 'PATH' value in the environnement env *************/
/* First get the different paths separated by ':'. Then, for each path, */
/* adds '/cmd' at the end. Then, checks if the calling process can		*/
/* access to the path command with the access function. F_OK will check */
/* if the file exists at this path. The X_OK grants execute permission. */
/************************************************************************/
char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*cmd_path;
	char	**path_array;
	char	*path_slash;

	i = 0;
	path_array = ft_split(ft_get_path_env(env), ":");
	while (path_array[i])
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

void	ft_fork_exec(char *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
		ft_exec(cmds, env);
	else
		waitpid(pid, NULL, 0); // cat | cat | ls ??
}

/********** Executes the command cmds in the environnement env **********/
/* 1. Split cmds if there is spaces in it.								*/
/* 2. Take the path, which is the command execution.					*/
/* 3. Execute the command with execve with its flags if needed.			*/
/* 4. Returns an error if execve returns an error.						*/
/************************************************************************/
void	ft_exec(char *cmds, char **env)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmds, " ");
	cmd_path = ft_get_path(cmd[0], env);

	// write(2, "\ncmd_path = ", 12);
	// write(2, cmd_path, ft_strlen(cmd_path));
	// write(2, "\ncmd[0] = ", 10);
	// write(2, cmd[0], ft_strlen(cmd[0]));
	// if (cmd[1])
	// {
	// 	write(2, "\ncmd[1] = ", 10);
	// 	write(2, cmd[1], ft_strlen(cmd[1]));
	// }
	
	if (execve(cmd_path, cmd, env) == -1)
	{
		ft_putstr(cmd[0], STDERR_FILENO);
		ft_putstr(": command not found\n", STDERR_FILENO);
		free_double_array(cmd);
		if (cmd_path)
			free(cmd_path);
		free(cmds);
		free_double_array(env);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}
