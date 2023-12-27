/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/26 21:34:55 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) av;
	(void) env;
	if (ac != 1)
	{
		ft_putstr("Error: Arguments not handled!\n", 2);
		return (1);
	}
	while (1)
	{
		line = readline("minishell>");
		if (!line)
		{
			return (clear_history(), 1);
		}
		add_history(line);
		if (ft_strcmp(line, "LOLILOL") == 0)
			break ;
		free(line);
	}
	free(line);
	clear_history();
	return (0);
}
