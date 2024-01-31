/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:09:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 17:08:29 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Copies a double array of characters and returns the copy.
*/
char	**cpy_env(char **base_env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	while (base_env[i])
		i++;
	env_cpy = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (base_env[i])
	{
		env_cpy[i] = ft_strdup(base_env[i]);
		i++;
	}
	return (env_cpy);
}

/*
 *	Returns the 'PWD' path from the environnement variable.
*/
char	*get_pwd(t_data *data)
{
	char	*pwd;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD", 3))
			pwd = ft_substr(data->env[i], 4, ft_strlen(data->env[i]) - 4);
		i++;
	}
	return (pwd);
}

/*
 *	Returns the 'OLDPWD' path from the environnement variable.
*/
char	*get_oldpwd(t_data *data)
{
	char	*oldpwd;
	int		i;

	oldpwd = NULL;
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "OLDPWD", 6))
			oldpwd = ft_substr(data->env[i], 7, ft_strlen(data->env[i]) - 7);
		i++;
	}
	return (oldpwd);
}

/*
 *	Returns the 'HOME' path from the environnement variable.
*/
char	*get_home_path(t_data *data)
{
	char	*home_path;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "HOME", 4))
			home_path = ft_substr(data->env[i], 5,
					ft_strlen(data->env[i]) - 5);
		i++;
	}
	return (home_path);
}
