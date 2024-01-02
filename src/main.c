/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/03 00:12:31 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handler(t_data *data)
{
	if (!ft_strncmp(data->line, "echo ", 5))
		echo(data);
	else if (!ft_strncmp(data->line, "cd ", 3))
		cd(data);
	else if (!ft_strcmp(data->line, "exit")
		|| !ft_strncmp(data->line, "exit ", 5))
		ft_exit(data);
	else
		ft_exec(data->line, data->env);
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

void	minishell(t_data *data, char **base_env)
{
	data->env = cpy_env(base_env);
	while (1)
	{
		data->line = readline("minishell>");
		if (!data->line)
		{
			free_double_array(data->env);
			clear_history();
			break ;
		}
		add_history(data->line);
		input_handler(data);
		free(data->line);
	}
}

int	main(int ac, char **av, char **base_env)
{
	t_data data;

	(void) av;
	if (ac != 1)
	{
		ft_putstr("Error: Too much arguments. No argument needed.\n", 2);
		return (1);
	}
	minishell(&data, base_env);
	return (0);
}
