/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:26:54 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 16:21:41 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error_exit(t_data *d, char **cmd, char *cmd_path, int status)
{
	free_double_array(cmd);
	if (cmd_path)
		free(cmd_path);
	free_all(d);
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

static void	exec_error2(t_data *data, char **cmd, char *cmd_path, DIR *dir)
{
	if (!dir && exec_error_is_file(cmd[0], ft_strdup("."))
		&& !access(cmd[0], R_OK))
	{
		exec_error_msg(cmd[0], "Permission denied", dir);
		exec_error_exit(data, cmd, cmd_path, 127);
	}
	else if (!dir && !exec_error_is_file(cmd[0], ft_strdup(".")))
	{
		exec_error_msg(cmd[0], "No such file or directory", dir);
		exec_error_exit(data, cmd, cmd_path, 127);
	}
	if (dir)
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
	else
	{
		exec_error2(data, cmd, cmd_path, dir);
	}
}
