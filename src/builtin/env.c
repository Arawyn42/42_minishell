/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:58:03 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 23:37:05 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Builtin: env.
 *	Prints all environnement lines, each on a new line.
 *	Exit status code is 0.
 *	If there is an argument other than spaces, it returns an error and the
 *	exit status code is 127.
*/
void	ft_print_env(char *command, t_data *data)
{
	int		i;
	char	*arg;

	i = 0;
	if (command[3] && command[4])
	{
		arg = ft_substr(command, 4, ft_strlen(command) - 4);
		ft_putstr("minishell: env: '", 2);
		ft_putstr(arg, 2);
		ft_putstr("': No such file or directory\n", 2);
		g_exit_status = 127;
		free(arg);
		return ;
	}
	while (data->env[i])
	{
		ft_putstr(data->env[i], 1);
		ft_putstr("\n", 1);
		i++;
	}
	g_exit_status = 0;
	free(command);
}

/*
 *	Refresh the env variable in data's structure with the new env entry.
*/
void	refresh_env(t_data *data, t_export *env)
{
	t_export	*ptr;
	char		**new_env;
	int			i;

	i = 0;
	while (data->env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	ptr = env;
	while (ptr)
	{
		new_env[i] = ft_strdup(ptr->content);
		i++;
		ptr = ptr->next;
	}
	free_double_array(data->env);
	data->env = new_env;
}

/*
 *	Converts env from char ** into a chained list and returns it.
*/
t_export	*convert_env_list(t_data *data)
{
	t_export	*env;
	t_export	*new;
	int			i;

	env = NULL;
	i = 0;
	while (data->env[i])
	{
		new = lst_new_node(ft_strdup(data->env[i]));
		lst_add_back(&env, new);
		i++;
	}
	return (env);
}

/*
 *	Adds a new variable in env and refreshes it.
*/
static void	add_env_new_var(t_data *data, char *var)
{
	int			i;
	t_export	*env;
	t_export	*new;

	i = 0;
	env = NULL;
	if (!var)
		return ;
	while (var[i])
	{
		if (var[i] == '=')
		{
			env = convert_env_list(data);
			new = lst_new_node(ft_strdup(var));
			lst_add_back(&env, new);
			refresh_env(data, env);
			free_export(&env);
		}
		i++;
	}
}

/*
 *	Adds a new variable in env if it doesn't exist and it has a value.
 *	If the variable already exists, refreshes its value if it's specified.
 *	If the variable doesn't exists and no value is specified, it is not added.
*/
void	add_env_var(t_data *data, char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (data->env[i])
	{
		var_name = get_var_name(data->env[i], 0);
		if (!ft_strncmp(var_name, var, ft_strlen(var_name)))
		{
			if (var[ft_strlen(var_name)] == '=')
			{
				free(data->env[i]);
				data->env[i] = ft_strdup(var);
				return (free(var_name));
			}
			else if (!var[ft_strlen(var_name)])
				return (free(var_name));
		}
		free(var_name);
		i++;
	}
	add_env_new_var(data, var);
}
