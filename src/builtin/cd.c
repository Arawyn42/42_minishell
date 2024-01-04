/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/03 00:36:23 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_data *data)
{
	int	i;
	int	j;
	char *path;

	i = 3;
	j = 0;
	if (count_single_quotes(data->line) % 2
		|| count_double_quotes(data->line) % 2)
	{
		ft_putstr("minishell: cd: quotes error\n", 2);
		return ;
	}
	while (data->line[i])
	{
		if (data->line[i] != 34 && data->line[i] != 39)
			j++;
		i++;
	}
	path = ft_calloc(j + 1, sizeof(char));
	if (!path)
		return ;
	i = 3;
	j = 0;
	while (data->line[i])
	{
		if (data->line[i] != 34 && data->line[i] != 39)
		{
			path[j] = data->line[i];
			j++;
		}
		i++;
	}
	if (chdir(path) == -1)
	{
		ft_putstr("minishell: cd: ", 2);
		ft_putstr(path, 2);
		ft_putstr(": No such file or directory\n", 2);
	}
	free(path);
}
