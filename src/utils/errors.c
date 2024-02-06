/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:27:52 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 14:38:29 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *var)
{
	ft_putstr("minishell: export: `", 2);
	ft_putstr(var, 2);
	ft_putstr("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

void	syntax_error_message(char *token_name, int len)
{
	ft_putstr("minishell: syntax error near unexpected token `", 2);
	write(2, token_name, len);
	write(2, "'\n", 2);
	g_exit_status = 2;
}

void	exit_no_errors(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
}
