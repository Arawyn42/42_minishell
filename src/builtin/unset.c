/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:39:33 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:53:07 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_var(t_export **first,
				t_export **previous, t_export **to_delete)
{
	if (*previous)
		(*previous)->next = (*to_delete)->next;
	else
		*first = (*to_delete)->next;
	free((*to_delete)->content);
	free(*(to_delete));
	*to_delete = NULL;
}

static void	unset_env(t_data *data, char *var)
{
	t_export	*env;
	t_export	*ptr;
	t_export	*previous;
	int			len;

	len = ft_strlen(var);
	env = convert_env_list(data);
	ptr = env;
	previous = NULL;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, var, len) && ptr->content[len] == '=')
		{
			delete_var(&env, &previous, &ptr);
			break ;
		}
		previous = ptr;
		ptr = ptr->next;
	}
	refresh_env(data, env);
	free_export(&env);
}

static void	unset_export(t_data *data, char *var)
{
	t_export	*ptr;
	t_export	*previous;
	char		*var_name;

	ptr = data->export;
	while (ptr)
	{
		var_name = get_var_name(ptr->content, 11);
		if (!ft_strncmp(var_name, var, ft_strlen(var_name))
			&& (!var[ft_strlen(var_name)] || var[ft_strlen(var_name)] == '='))
		{
			delete_var(&(data->export), &previous, &ptr);
			sort_export(data);
			return (free(var_name));
		}
		free(var_name);
		previous = ptr;
		ptr = ptr->next;
	}
}

static void	unset_var(t_data *data, char *var, int error)
{
	if (error)
	{
		ft_putstr("minishell: unset: `", 2);
		ft_putstr(var, 2);
		ft_putstr("': not a valid identifier\n", 2);
	}
	else
	{
		unset_env(data, var);
		unset_export(data, var);
	}
}

void	ft_unset(t_data *data)
{
	char	*var;
	int		error;
	int		i;
	int		j;

	i = 5;
	while (data->line[i])
	{
		j = 0;
		error = 0;
		i++;
		while (data->line[i + j] && data->line[i + j] != ' ')
		{
			if (data->line[i + j] == '=')
				error = 1;
			j++;
		}
		var = ft_substr(data->line, i, j);
		unset_var(data, var, error);
		free(var);
		i += j;
	}
}
