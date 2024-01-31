/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:39:33 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/30 21:16:54 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 *	Deletes a node from a t_export chained list, corresponding to the
 *	variable to remove, frees the node's content, frees the node
 *	and sets it to NULL.
*/
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

/*
 *	Removes a variable form env if it is found in it.
*/
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

/*
 *	Removes a variable from the export list if it is found in it.
*/
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

/*
 *	In case of error, exit status code is 1 and the error is printed.
 *	If no error, removes the variable from env and export if it exists.
*/
static void	unset_var(t_data *data, char *var, int error)
{
	if (error)
	{
		ft_putstr("minishell: unset: `", 2);
		ft_putstr(var, 2);
		ft_putstr("': not a valid identifier\n", 2);
		g_exit_status = 1;
	}
	else
	{
		unset_env(data, var);
		unset_export(data, var);
	}
}

/*
 *	Removes variables from export, and form env if it exists in it.
 *	In case of invalid entry, returns an error and sets the exit status code
 *	to 1, then continues removing variables if other arguments are specified.
 *	If no error is returned, exit status code is 0.
*/
void	ft_unset(char *command, t_data *data)
{
	char	*var;
	int		error;
	int		i;
	int		j;

	i = 5;
	g_exit_status = 0;
	while (command[i])
	{
		j = 0;
		error = 0;
		i++;
		while (command[i + j] && command[i + j] != ' ')
		{
			if (command[i + j] == '=')
				error = 1;
			j++;
		}
		var = ft_substr(command, i, j);
		unset_var(data, var, error);
		free(var);
		i += j;
	}
}
