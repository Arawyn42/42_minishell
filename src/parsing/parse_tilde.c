/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:40:10 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 17:21:43 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Calculates the length of the HOME path and modifies the total length's
 *	pointer of the parsed string accordingly.
*/
void	tilde_len(t_data *data, int *i, int *len)
{
	char	*home_path;

	if (data->line[*i + 1])
		(*i)++;
	home_path = get_home_path(data);
	if (home_path)
	{
		*len += ft_strlen(home_path);
		free(home_path);
	}
}

/*
 *	Replaces the tilde '~' by the HOME path.
*/
void	parse_tilde(t_data *data, char *newline, int *i, int *j)
{
	char	*home_path;
	int		k;

	if (data->line[*i + 1])
		(*i)++;
	home_path = get_home_path(data);
	k = 0;
	while (home_path && home_path[k])
	{
		newline[*j] = home_path[k];
		(*j)++;
		k++;
	}
	if (home_path)
		free(home_path);
}
