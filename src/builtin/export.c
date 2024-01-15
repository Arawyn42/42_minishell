/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:03:53 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/15 19:14:22 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *export_line, int i)
{
	char	*var_name;
	int		start;

	start = i;
	while (export_line[i])
	{
		if (export_line[i] == '=')
			break ;
		i++;
	}
	var_name = ft_substr(export_line, start, i - start);
	return (var_name);
}

static void	add_export_new_var(t_data *data, char *var)
{
	t_export	*new;

	if (!var)
		return ;
	new = lst_new_node(convert_env_export(var));
	lst_add_back(&data->export, new);
	sort_export(data);
}

static void	add_export_var(t_data *data, char *var)
{
	t_export	*ptr;
	char		*var_name;

	add_env_var(data, var);
	ptr = data->export;
	while (ptr)
	{
		var_name = get_var_name(ptr->content, 11);
		if (!ft_strncmp(var_name, var, ft_strlen(var_name)))
		{
			if (var[ft_strlen(var_name)] == '=')
			{
				free(ptr->content);
				ptr->content = convert_env_export(var);
				sort_export(data);
				return (free(var_name));
			}
			else if (!var[ft_strlen(var_name)])
				return (free(var_name));
		}
		free(var_name);
		ptr = ptr->next;
	}
	add_export_new_var(data, var);
}

static void	export_var(t_data *data)
{
	char	*var;
	int		i;
	int		j;

	i = 6;
	while (data->line[i])
	{
		j = 0;
		i++;
		while (data->line[i + j] && data->line[i + j] != ' ')
			j++;
		var = ft_substr(data->line, i, j);
		if (var[0] == '=')
		{
			ft_putstr("minishell: export: `", 2);
			ft_putstr(var, 2);
			ft_putstr("': not a valid identifier\n", 2);
		}
		else
			add_export_var(data, var);
		free(var);
		i += j;
	}
}

void	ft_export(t_data *data)
{
	if (!data->line[6])
	{
		sort_export(data);
		print_export(data);
	}
	else if (data->line[6] == ' ')
	{
		export_var(data);
	}
}
