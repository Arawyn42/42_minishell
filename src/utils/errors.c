/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:27:52 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 23:11:29 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_message(char *token_name, int len)
{
	ft_putstr("minishell: syntax error near unexpected token `", 2);
	write(2, token_name, len);
	write(2, "'\n", 2);
	g_exit_status = 2;
}

void	exit_error(const char *msg)
{
	perror(msg);
	g_exit_status = 1;
	exit(g_exit_status);
}

void	exit_no_errors(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
}
