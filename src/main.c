/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/27 23:18:09 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handler(char **env, char *line)
{
	(void) env;
	if (ft_strcmp(line, "exit") == 0)
	{
		ft_putstr("exit\n", 1);
		clear_history();
		free(line);
		exit(EXIT_SUCCESS);
	}
	else
		ft_exec(line, env);
}

char	**cpy_env(char **base_env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	while (base_env[i])
		i++;
	env_cpy = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (base_env[i])
	{
		env_cpy[i] = ft_strdup(base_env[i]);
		i++;
	}
	return (env_cpy);
}

int	minishell(char **base_env)
{
	char	*line;
	char	**env;

	env = cpy_env(base_env);
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			return (clear_history(), 0);
		add_history(line);
		input_handler(env, line);
		free(line);
	}
	return (1);
}

int	main(int ac, char **av, char **base_env)
{
	(void) av;
	if (ac != 1)
	{
		ft_putstr("Error: Too much arguments. No argument needed.\n", 2);
		return (1);
	}
	if (!minishell(base_env))
		return (clear_history(), 1);
	clear_history();
	return (0);
}
