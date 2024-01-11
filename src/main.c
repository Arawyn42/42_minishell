/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/11 20:01:41 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	command_launcher(t_data *data)
{
	data->line = parse_line(data->line, data->env);
	if (!data->line)
		return (1);
	if (!ft_strncmp(data->line, "pwd", 3)
		&& (data->line[3] == ' ' || !data->line[3]))
		ft_pwd();
	else if (!ft_strncmp(data->line, "echo ", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->line, "cd", 2))
		ft_cd(data);
	else if (!ft_strcmp(data->line, "exit")
		|| !ft_strncmp(data->line, "exit ", 5))
		ft_exit(data);
	else
		return (0);
	return (1);
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
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	data->env = cpy_env(base_env);
	data->prompt = NULL;
	while (1)
	{
		refresh_prompt(data);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		data->line = readline(data->prompt);
		if (!data->line)
		{
			free_double_array(data->env);
			clear_history();
			break ;
		}
		add_history(data->line);
		if (ft_strlen(data->line) != 0)
			input_handler(data);
		else
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
