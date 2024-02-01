/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:46:43 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/01 20:44:18 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Checks all parsing conditions according to bash rules, for single quotes,
 *	double quotes, '$', '\', '~' and '*'.
 *	Returns 1 to print the character the index is at, or 0 to not print it.
*/
static int	parse_conditions(char *line, int i, int *inq, int parse_quotes)
{
	if (i >= 1 && line[i] == '?' && line[i - 1] == '$')
		return (0);
	if (line[i] == '~' && !inq[0] && !inq[1] && line[i - 1] == ' '
		&& (line[i + 1] == ' ' || line[i + 1] == '/' || !line[i + 1]))
		return (0);
	if (line[i] == '*' && !inq[0] && !inq[1] && (i == 0 || line[i - 1] != '\\'))
		return (0);
	if ((parse_quotes && line[i] != '\"' && line[i] != '\'' && line[i] != '\\')
		|| (!parse_quotes && line[i] != '\\'))
		return (1);
	if (i > 0 && line[i - 1] == '\\' && !inq[0])
		return (1);
	if (inq[0] && line[i] != '\'')
		return (1);
	if (inq[1] && line[i] != '\"' && line[i] != '\\')
		return (1);
	if (line[i] == '\\' && inq[1] && (line[i + 1] == '\'' || line[i + 1] == ' '))
		return (1);
	return (0);
}

/*
 *	Replaces following multiple spaces by one space in the parsed string.
*/
void	parse_spaces(char *line, int *i)
{
	while (line[*i] == ' ' && line[*i + 1] == ' ')
		(*i)++;
}

/*
 *	Calculates the total length of the parsed string in order to allocate
 *	the good amount of memory space for it.
*/
void	new_line_len(t_data *data, int *len, int **quotes, int parse_quotes)
{
	int	i;

	i = 0;
	while ((size_t) i < ft_strlen(data->line) && data->line[i])
	{
		if (data->line[i] == ' ' && !(*quotes)[0] && !(*quotes)[1])
			parse_spaces(data->line, &i);
		if (data->line[i] == '\\' && !(*quotes)[0] && !(*quotes)[1])
			i++;
		if (data->line[i] == '$' && !(*quotes)[0] && (i == 0
				|| data->line[i - 1] != '\\') && data->line[i + 1] != '~')
			dollar_var_len(data, &i, len);
		if (data->line[i] == '~' && !(*quotes)[0] && !(*quotes)[1]
			&& data->line[i - 1] == ' ' && (data->line[i + 1] == ' '
				|| data->line[i + 1] == '/' || !data->line[i + 1]))
			tilde_len(data, &i, len);
		if (data->line[i] == '*' && !(*quotes)[0] && !(*quotes)[1]
			&& (i == 0 || data->line[i - 1] != '\\'))
			wildcard_len(data, &i, len);
		if (parse_conditions(data->line, i, *quotes, parse_quotes))
			(*len)++;
		if ((data->line[i] == '\'' || data->line[i] == '\"'))
			in_or_out_quotes(data->line, &(*quotes)[0], &(*quotes)[1], i);
		i++;
	}
}

/*
 *	Parses a string according to the bash's rules, for single quotes ',
 *	double quotes ", tilde ~, wildcard *, backslash \ and environnement
 *	variables $. Also parses spaces to put only one space between two
 *	non-space characters.
*/
static void	parsed_line(t_data *data, char *new_line,
		int **quotes, int parse_quotes)
{
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	while ((size_t) ++(i[0]) < ft_strlen(data->line) && data->line[i[0]])
	{
		if (data->line[i[0]] == ' ' && !(*quotes)[0] && !(*quotes)[1])
			parse_spaces(data->line, &i[0]);
		if (data->line[i[0]] == '\\' && !(*quotes)[0] && !(*quotes)[1])
			(i[0])++;
		if (data->line[i[0]] == '$' && !(*quotes)[0] && (i[0] == 0
				|| data->line[i[0] - 1] != '\\') && data->line[i[0] + 1] != '~')
			parse_dollar_var(data, new_line, &i[0], &i[1]);
		if (data->line[i[0]] == '~' && !(*quotes)[0] && !(*quotes)[1]
			&& data->line[i[0] - 1] == ' ' && (data->line[i[0] + 1] == ' '
				|| data->line[i[0] + 1] == '/' || !data->line[i[0] + 1]))
			parse_tilde(data, new_line, &i[0], &i[1]);
		if (data->line[i[0]] == '*' && !(*quotes)[0] && !(*quotes)[1]
			&& (i[0] == 0 || data->line[i[0] - 1] != '\\'))
			parse_wildcard(data->line, new_line, &i[0], &i[1]);
		if (parse_conditions(data->line, i[0], *quotes, parse_quotes))
			new_line[(i[1])++] = data->line[i[0]];
		if ((data->line[i[0]] == '\'' || data->line[i[0]] == '\"'))
			in_or_out_quotes(data->line, &(*quotes)[0], &(*quotes)[1], i[0]);
	}
}

/*
 *	Trims spaces and parenthesis in a string, then parses it according to
 *	the bash's rules. Returns the parsed string.
 *	If parse_quotes != 0, it parses the line without printing closed quotes.
 *	Else if parse_quotes == 0, it parses the line but prints all quotes.
*/
char	*parse_line(char *line, char **env, int parse_quotes)
{
	t_data	data;
	char	*new_line;
	int		*quotes;
	int		len;

	data.line = ft_strtrim(line, " ()");
	data.env = env;
	quotes = ft_calloc(2, sizeof(int));
	data.line = unclosed_quotes(&data);
	free(line);
	len = 0;
	new_line_len(&data, &len, &quotes, parse_quotes);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	parsed_line(&data, new_line, &quotes, parse_quotes);
	free(data.line);
	free(quotes);
	return (new_line);
}
