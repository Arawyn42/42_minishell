/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:27:52 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/30 16:37:21 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_message(char *token_name, int len)
{
	ft_putstr("minishell: syntax error near unexpected token `", 2);
	write(2, token_name, len);
	write(2, "'\n", 2);
}

void	redirection_error_message(char *token_name, int len)
{
	if (token_name)
	{
		ft_putstr("minishell: syntax error near unexpected token `", 2);
		write(2, token_name, len);
		write(2, "'\n", 2);
	}
	else
	{
		ft_putstr("minishell: syntax error: ", 2);
		ft_putstr("unexpected pipe or redirection\n", 2);
	}
}

void	exit_error(const char *msg)
{
	perror(msg);
	g_exit_status = 1;
	exit(g_exit_status);
}
