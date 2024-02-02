/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:26:54 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/02 17:01:19 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error_exit(t_data *data, char **cmd, char *cmd_path, int status)
{
	free_double_array(cmd);
	if (cmd_path)
		free(cmd_path);
	free_all(data);
	g_exit_status = status;
	exit(g_exit_status);
}

static void	exec_error_msg(char *cmd, char *msg, DIR *dir)
{
	ft_putstr("minishell: ", 2);
	ft_putstr(cmd, 2);
	ft_putstr(": ", 2);
	ft_putstr(msg, 2);
	ft_putstr("\n", 2);
	closedir(dir);
}

static int	exec_error_is_file2(struct dirent *dr, char *name, char *dir_name)
{
	char	*dir_n;

	if (dr->d_type == 4 && !ft_strncmp(name, dr->d_name,
			ft_strlen(dr->d_name)))
	{
		dir_n = ft_strjoin(dir_name, "/");
		free(dir_name);
		dir_name = ft_strjoin(dir_n, dr->d_name);
		free(dir_n);
		return (exec_error_is_file(name + ft_strlen(dr->d_name) + 1,
			dir_name));
	}
	if (!ft_strncmp(name, dr->d_name, ft_strlen(name)))
	if (!ft_strncmp(name, dr->d_name, ft_strlen(name)))
		return (free(dir_name), 1);
	return (0);
}

int	exec_error_is_file(char *cmd, char *dir_name)
{
	char			*name;
	DIR				*dir;
	struct dirent	*dr;

	if (cmd[0] == '.' && cmd[1] == '/' && cmd[ft_strlen(cmd) - 1] == '/')
		name = ft_substr(cmd, 2, ft_strlen(cmd) - 3);
	else if (cmd[0] == '.' && cmd[1] == '/' && cmd[ft_strlen(cmd) - 1] != '/')
		name = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
	else
		name = ft_strdup(cmd);
	dir = opendir(dir_name);
	dr = readdir(dir);
	while (dr)
	{
		if (exec_error_is_file2(dr, name, dir_name))
			return (closedir(dir), free(name), 1);
		dr = readdir(dir);
	}
	return (closedir(dir), free(name), free(dir_name), 0);
}

static void	exec_error2(t_data *data, char **cmd, char *cmd_path, DIR *dir)
{
	if (!dir && !exec_error_is_file(cmd[0], ft_strdup(".")))
	{
		exec_error_msg(cmd[0], "No such file or directory", dir);
		exec_error_exit(data, cmd, cmd_path, 127);
	}
	else if (dir)
	{
		exec_error_msg(cmd[0], "Is a directory", dir);
		exec_error_exit(data, cmd, cmd_path, 126);
	}
	perror(cmd[0]);
	exec_error_exit(data, cmd, cmd_path, 126);
}

void	exec_error(t_data *data, char **cmd, char *cmd_path)
{
	DIR	*dir;

	dir = opendir(cmd[0]);
	if (!ft_strchr(cmd[0], '/'))
	{
		exec_error_msg(cmd[0], "command not found", dir);
		exec_error_exit(data, cmd, cmd_path, 127);
	}
	else if (!dir && exec_error_is_file(cmd[0], ft_strdup("."))
			&& access(cmd[0], R_OK))
	{
		exec_error_msg(cmd[0], "Not a directory", dir);
		exec_error_exit(data, cmd, cmd_path, 126);
	}
	else if (!dir && exec_error_is_file(cmd[0], ft_strdup("."))
			&& !access(cmd[0], R_OK))
	{
		// printf("errno = %d\n", errno);
		exec_error_msg(cmd[0], "Permission denied", dir);
		exec_error_exit(data, cmd, cmd_path, 127);
	}
	else
		exec_error2(data, cmd, cmd_path, dir);
}
