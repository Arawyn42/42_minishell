/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/30 02:14:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirection(char **cmds, int *index, t_data *data)
{
	int		fd;
	int		saved_stdout;
	char	*file;

	saved_stdout = dup(STDOUT_FILENO);
	file = cmds[*index + 1];
	if (!file)
		return (redirection_error_message());
	file = parse_line(ft_strdup(file), data->env);
	fd = open(file, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		write(2, file, ft_strlen(file));
		perror("\1");
		(*index)++;
		return (free(file));
	}
	data->line = parse_line(ft_strdup(cmds[*index]), data->env);
	free(file);
	(*index)++;
	dup2(fd, STDIN_FILENO);
	if (!builtin_launcher(data))
		ft_fork_exec(data->line, data->env);
	dup2(saved_stdout, STDOUT_FILENO);
}

void	output_redirection(char **cmds, int *index, int oflags, t_data *data)
{
	int		fd;
	int		saved_stdout;
	char	*file;

	saved_stdout = dup(STDOUT_FILENO);
	file = cmds[*index + 1];
	if (!file)
		return (redirection_error_message());
	file = parse_line(ft_strdup(file), data->env);
	fd = open(file, oflags, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		write(2, file, ft_strlen(file));
		(*index)++;
		perror("\1");
		return (free(file));
	}
	data->line = parse_line(ft_strdup(cmds[*index]), data->env);
	free(file);
	(*index)++;
	dup2(fd, STDOUT_FILENO);
	if (!builtin_launcher(data))
		ft_fork_exec(data->line, data->env);
	dup2(saved_stdout, STDOUT_FILENO);
}
