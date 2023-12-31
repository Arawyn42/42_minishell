/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:51:21 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/08 23:58:31 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_prompt(t_data *data)
{
	char	*second_part;
	char	*home_path;
	char	*pwd;
	char	*prompt;

	home_path = get_home_path(data);
	pwd = get_pwd(data);
	if (!ft_strncmp(pwd, home_path, ft_strlen(home_path)))
	{
		second_part = ft_substr(pwd, ft_strlen(home_path),
			ft_strlen(pwd) - ft_strlen(home_path));
		prompt = ft_strjoin("minishell:~", second_part);
	}
	else
	{
		second_part = ft_strjoin("~", pwd);
		prompt = ft_strjoin("minishell:", second_part);
	}
	free(home_path);
	free(pwd);
	free(second_part);
	if (data->prompt)
		free(data->prompt);
	data->prompt = ft_strjoin(prompt, "$ ");
	free(prompt);
}

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

void	set_old_pwd(t_data *data)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = getcwd(NULL, 0);
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

void	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr(pwd, 1);
	ft_putstr("\n", 1);
	free(pwd);
}
