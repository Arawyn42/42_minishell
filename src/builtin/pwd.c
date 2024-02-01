/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:51:21 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/01 17:14:43 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Refreshes the program's prompt with the current directory's path.
 *	Follows the bash's prompt behaviour.
*/
void	refresh_prompt(t_data *data)
{
	char	*second_part;
	char	*home_path;
	char	*pwd;
	char	*prompt;

	home_path = get_home_path(data);
	pwd = getcwd(NULL, 0);
	if (!ft_strncmp(pwd, home_path, ft_strlen(home_path)))
	{
		second_part = ft_substr(pwd, ft_strlen(home_path),
				ft_strlen(pwd) - ft_strlen(home_path));
		prompt = ft_strjoin(PROMPT_HOME, second_part);
	}
	else
	{
		second_part = ft_strdup(pwd);
		prompt = ft_strjoin(PROMPT_ROOT, second_part);
	}
	free(home_path);
	free(pwd);
	free(second_part);
	if (data->prompt)
		free(data->prompt);
	data->prompt = ft_strjoin(prompt, "\001\e[0m\002$ ");
	free(prompt);
}

/*
 *	Sets the 'PWD' env variable on the current location.
*/
void	set_pwd(t_data *data)
{
	int		i;
	char	*new_pwd;

	i = 0;
	new_pwd = getcwd(NULL, 0);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD", 3))
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin("PWD=", new_pwd);
		}
		i++;
	}
	free(new_pwd);
}

/*
 *	Sets the 'OLDPWD' env variable on the previous location.
*/
void	set_old_pwd(t_data *data, char *path)
{
	int		i;
	char	*old_pwd;

	i = 0;
	if (!path)
		old_pwd = getcwd(NULL, 0);
	else
		old_pwd = ft_strdup(path);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "OLDPWD", 3))
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
	free(old_pwd);
}

/*
 *	Prints the current location on the standard output.
 *	this does NOT depends on the 'PWD' env variable.
 *	Exit status code is 0.
*/
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr(pwd, 1);
	ft_putstr("\n", 1);
	free(pwd);
	g_exit_status = 0;
}
