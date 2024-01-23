/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:58:03 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/18 18:31:22 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_putstr(data->env[i], 1);
		ft_putstr("\n", 1);
		i++;
	}
	exit_status = 0;
}

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
