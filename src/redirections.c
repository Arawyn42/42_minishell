/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/31 16:18:51 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirection(t_data *data, int *i)
{
	int		fd;
	int		saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (!data->command[*i + 1])
		return (ft_putstr("!!!PARSING ERROR!!!\n", 2), exit(EXIT_FAILURE)); // remove
	fd = open(data->command[*i + 1], O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(data->command[*i + 1], 2);
		perror("\1");
		(*i)++;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	if (data->command[*i - 1])
		if (!builtin_launcher(data->command[*i - 1], data))
			ft_fork_exec(data->command[*i - 1], data);
	(*i)++;
	dup2(saved_stdout, STDOUT_FILENO);
}

void	output_redirection(t_data *data, int *i, int oflags)
{
	int		fd;
	int		saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (!data->command[*i + 1])
		return (ft_putstr("!!!PARSING ERROR!!!\n", 2), exit(EXIT_FAILURE)); // remove
	fd = open(data->command[*i + 1], oflags, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(data->command[*i + 1], 2);
		(*i)++;
		perror("\1");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	if (data->command[*i - 1])
		if (!builtin_launcher(data->command[*i - 1], data))
			ft_fork_exec(data->command[*i - 1], data);
	dup2(saved_stdout, STDOUT_FILENO);
	(*i)++;
}
