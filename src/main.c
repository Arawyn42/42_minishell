/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 20:36:40 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;
int	g_sigint;

static void	minishell(t_data *data, int	saved_stdin)
{
	int	is_old_line_null;

	is_old_line_null = 1;
	while (1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		if (g_sigint && is_old_line_null)
			ft_putstr("\n", 1);
		g_sigint = 0;
		refresh_prompt(data);
		data->line = readline(data->prompt);
		if (!data->line && !g_sigint)
			return (ft_putstr("exit\n", 1), free_all(data));
		if (!data->line && g_sigint)
			ft_putstr("\n", 1);
		is_old_line_null = data->line != NULL;
		if (ft_strlen(data->line) > 0)
		{
			if (!is_unclosed_quotes(data) && ft_strlen(data->line) > 0)
				add_history(data->line);
			parse_and_launch(data);
		}
		free(data->line);
	}
}

static void	minishell_with_c_flag(t_data *data, char *line)
{
	data->line = ft_strdup(line);
	if (ft_strlen(data->line) > 0)
		parse_and_launch(data);
	free_all(data);
}

int	main(int ac, char **av, char **base_env)
{
	t_data	data;

	(void) av;
	if ((ac != 1 && ac != 3) || (ac == 3 && ft_strcmp(av[1], "-c")))
	{
		ft_putstr("Error: Wrong arguments.\nUsage:\nTo launch minishell:", 2);
		ft_putstr("\t\t./minishell\nTo execute one command line:", 2);
		ft_putstr("\t./minishell -c \"COMMAND_LINE\"\n", 2);
		return (1);
	}
	data.env = cpy_env(base_env);
	data.prompt = NULL;
	data.command = NULL;
	init_export(&data);
	g_exit_status = 0;
	g_sigint = 0;
	if (ac == 3)
		return (minishell_with_c_flag(&data, av[2]), 0);
	signal(SIGINT, signals_handler);
	sigquit_handler();
	minishell(&data, dup(STDIN_FILENO));
	return (0);
}
