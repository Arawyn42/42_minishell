/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:09:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/09 15:52:05 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Increments the value of the SHLVL environnement variable.
*/
static char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*level;
	char	*res;

	level = ft_substr(shlvl, 6, ft_strlen(shlvl) - 6);
	lvl = ft_atoi(level);
	free(level);
	lvl++;
	level = ft_itoa(lvl);
	res = ft_strjoin("SHLVL=", level);
	free(level);
	return (res);
}

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
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (base_env[i])
	{
		if (!ft_strncmp(base_env[i], "SHLVL=", 6))
			env_cpy[i] = change_shlvl(base_env[i]);
		else
			env_cpy[i] = ft_strdup(base_env[i]);
		i++;
	}
	return (env_cpy);
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
	home_path = NULL;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "HOME", 4))
			home_path = ft_substr(data->env[i], 5,
					ft_strlen(data->env[i]) - 5);
		i++;
	}
	return (home_path);
}
