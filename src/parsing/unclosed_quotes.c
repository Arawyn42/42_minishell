/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:44:46 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/05 23:32:26 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Prints an error when CTRL + D (EOF) signal is received.
 *	In this case. exit status code is 2.
 *	If CTRL + C (SIGINT) is received, prints no error.
*/
static char	*unclosed_quotes_error(char *line, char *quote, char signal)
{
	if (signal == 'd')
	{
		ft_putstr("minishell: unexpected EOF while looking for ", 2);
		ft_putstr("matching `", 2);
		ft_putstr(quote, 2);
		ft_putstr("'\nminishell: syntax error: unexpected", 2);
		ft_putstr(" end of file\n", 2);
		g_exit_status = 2;
	}
	add_history(line);
	free(line);
	return (ft_strdup(""));
}

/*
 *	Opens a here_document in case of unclosed double quotes, with " as LIMITER.
*/
static char	*unclosed_double(char *str)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line && g_sigint)
			return (unclosed_quotes_error(str, "\"", 'c'));
		line = ft_strjoin(str, "\n");
		free(str);
		str = ft_strjoin(line, new_line);
		free(new_line);
		free(line);
		if (!new_line && !g_sigint)
			return (unclosed_quotes_error(str, "\"", 'd'));
		if (count_double_quotes(str) % 2 == 0)
			break ;
	}
	add_history(str);
	return (str);
}

/*
 *	Opens a here_document in case of unclosed single quotes, with ' as LIMITER.
*/
static char	*unclosed_single(char *str)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (!new_line && g_sigint)
			return (unclosed_quotes_error(str, "\'", 'c'));
		line = ft_strjoin(str, "\n");
		free(str);
		str = ft_strjoin(line, new_line);
		free(new_line);
		free(line);
		if (!new_line && !g_sigint)
			return (unclosed_quotes_error(str, "\'", 'd'));
		if (count_single_quotes(str) % 2 == 0)
			break ;
	}
	add_history(str);
	return (str);
}

/*
 *	Returns 1 if the line contains an unclosed quote (double or single).
 *	Returns 0 if not.
*/
int	is_unclosed_quotes(char *line)
{
	if (count_double_quotes(line) % 2 == 0
		&& count_single_quotes(line) % 2 == 0)
		return (0);
	return (1);
}

/*
 *	Opens a here_document in case of unclosed quotes,
 *	until the quotes are closed.
*/
char	*unclosed_quotes(char *line)
{
	int		i;

	i = 0;
	if (!is_unclosed_quotes(line))
		return (line);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			line = unclosed_single(line);
			break ;
		}
		else if (line[i] == '\"')
		{
			line = unclosed_double(line);
			break ;
		}
		i++;
	}
	return (line);
}
