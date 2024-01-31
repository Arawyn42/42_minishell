/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:45:07 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/31 18:42:07 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Redirects SIGQUIT signal to be ignored. SIGQUIT (CTRL + \) does nothing.
*/
void	sigquit_handler(void)
{
	struct sigaction	s;

	ft_bzero(&s, sizeof(s));
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
}

/*
 *	Handles SIGINT signal. I SIGINT (CTRL + c) is received,
 *	exit status code is 130. Exits the children processes.
*/
void	signals_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint = 1;
		close(0);
		g_exit_status = 130;
	}
}
