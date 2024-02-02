/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:12:19 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/02 03:40:15 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *var)
{
	ft_putstr("minishell: export: `", 2);
	ft_putstr(var, 2);
	ft_putstr("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

/*
 *	Initializes the export list by copying all env lines in export nodes.
*/
void	init_export(t_data *data)
{
	int			i;
	t_export	*new;

	data->export = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "_=", 2))
		{
			new = lst_new_node(convert_env_export(data->env[i]));
			lst_add_back(&data->export, new);
		}
		i++;
	}
}

/*
 *	Converts an env line into an export line and returns it.
*/
char	*convert_env_export(char *env_line)
{
	char	*export_line;
	char	*second_part;
	int		i;
	int		j;

	second_part = ft_calloc(ft_strlen(env_line) + 3, sizeof(char));
	if (!second_part)
		return (NULL);
	i = 0;
	j = 0;
	while (env_line[j] && env_line[j] != '=')
		second_part[i++] = env_line[j++];
	if (env_line[j++] == '=')
	{
		second_part[i++] = '=';
		second_part[i++] = '\"';
		while (env_line[j])
			second_part[i++] = env_line[j++];
		second_part[i++] = '\"';
	}
	export_line = ft_strjoin("declare -x ", second_part);
	free(second_part);
	return (export_line);
}

/*
 *	Sorts the export list according to the ASCII order.
*/
void	sort_export(t_data *data)
{
	t_export	*ptr;
	t_export	*ptr2;
	char		*tmp;

	ptr = data->export;
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			if (ft_strcmp(ptr->content, ptr2->content) > 0)
			{
				tmp = ft_strdup(ptr->content);
				free(ptr->content);
				ptr->content = ft_strdup(ptr2->content);
				free(ptr2->content);
				ptr2->content = ft_strdup(tmp);
				free(tmp);
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

/*
 *	Prints each export node on a new line on the standard output.
*/
void	print_export(t_data *data)
{
	t_export	*ptr;

	ptr = data->export;
	while (ptr)
	{
		ft_putstr(ptr->content, 1);
		ft_putstr("\n", 1);
		ptr = ptr->next;
	}
}
