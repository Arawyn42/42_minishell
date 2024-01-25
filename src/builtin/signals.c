/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:45:07 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:47:55 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(void)
{
	struct sigaction	s;

	ft_bzero(&s, sizeof(s));
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
}

void	signals_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint = 1;
		close(0);
		g_exit_status = 130;
	}
	if (!g_pid)
	{
		exit(g_exit_status);
	}
}
