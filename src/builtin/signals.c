/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:45:07 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/24 16:52:01 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals()
{
	// g_exit_status = 0;
	g_sigint = 0;
}

void	sigint_handler(int signum)
{
	// if (signum == SIGINT && !g_pid)
	// {
	// 	// g_sigint = 1;
	// 	// close(0);
	// }
	if (signum == SIGINT)
	{
		g_sigint = 1;
		ft_putstr("\n", 1);
		close(0);
		g_exit_status = 130;
	}
	
}
