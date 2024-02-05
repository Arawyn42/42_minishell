/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:13:31 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 18:14:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 *	Frees a double array of characters
*/
void	free_double_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
 *	At the end of the program, frees all allocated memory
 *	if the corresponding space exists.
*/
void	free_all(t_data *data)
{
	rl_clear_history();
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->env)
		free_double_array(data->env);
	if (data->export)
		free_export(&data->export);
	if (data->command)
		free_command(data->command);
}

/*
 *	Frees the export list and sets it on NULL.
*/
void	free_export(t_export **lst)
{
	if (lst && *lst)
	{
		free_export(&(*lst)->next);
		free((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}

void	free_command(char **command)
{
	int	i;

	i = 1;
	while (command[i])
		free(command[i++]);
	free(command);
}
