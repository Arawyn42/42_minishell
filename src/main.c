/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/22 18:53:10 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

int	builtin_launcher(t_data *data)
{
	if (!data->line)
		return (1);
	if (!ft_strncmp(data->line, "pwd", 3)
		&& (data->line[3] == ' ' || !data->line[3]))
		ft_pwd();
	else if (!ft_strcmp(data->line, "echo")
		|| !ft_strncmp(data->line, "echo ", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->line, "cd", 2))
		ft_cd(data);
	else if (!ft_strcmp(data->line, "env")
		|| !ft_strncmp(data->line, "env ", 4))
		ft_print_env(data);
	else if (!ft_strcmp(data->line, "export")
		|| !ft_strncmp(data->line, "export ", 7))
		ft_export(data);
	else if (!ft_strcmp(data->line, "unset")
		|| !ft_strncmp(data->line, "unset ", 6))
		ft_unset(data);
	else
		return (0);
	return (1);
}

void	minishell(t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		refresh_prompt(data);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		data->line = readline(data->prompt);
		if (!data->line)
		{
			free_double_array(data->env);
			clear_history(); // forbidden
			break ;
		}
		if (ft_strlen(data->line) != 0 && !is_exit(data))
		{
			add_history(data->line);
			parse_logic_operators(data);
		}
	}
}

int	main(int ac, char **av, char **base_env)
{
	t_data	data;

	(void) av;
	if (ac != 1)
	{
		ft_putstr("Error: Too much arguments. No argument needed.\n", 2);
		return (1);
	}
	data.env = cpy_env(base_env);
	data.prompt = NULL;
	init_export(&data);
	exit_status = 0;
	minishell(&data);
	return (0);
}
