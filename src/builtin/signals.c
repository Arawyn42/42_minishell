/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:45:07 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/24 01:34:48 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT && !g_pid)
	{
		g_sigint = 1;
		ft_putstr("\n", 1);
		g_exit_status = 130;
		// ft_putstr("IN CHILD PROCESS\n", 2);
		close(0);
	}
	else if (signum == SIGINT && g_pid)
	{
		g_sigint = 1;
		ft_putstr("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// ft_putstr("IN PARENT PROCESS\n", 2);
		g_exit_status = 130;
	}
	
}
