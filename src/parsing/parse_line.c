/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:46:43 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:51:23 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_dollar_value(t_data *data, char *new_line, int *i, int *j)
{
	char	*var;
	int		k;

	k = 0;
	while (data->line[*i + k] && data->line[*i + k] != ' '
		&& data->line[*i + k] != '\'' && data->line[*i + k] != '\"'
		&& data->line[*i + k] != '/' && data->line[*i + k] != '\\')
		k++;
	var = get_dollar_var(data, i, &k);
	k = 0;
	while (var && var[k])
	{
		new_line[*j] = var[k];
		(*j)++;
		k++;
	}
	if (var)
		free(var);
}

static void	parse_dollar_var(t_data *data, char *new_line, int *i, int *j)
{
	char	*ex_stat;
	int		k;

	k = 0;
	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0')
		return ;
	(*i)++;
	if (data->line[*i] == '?')
	{
		ex_stat = ft_itoa(g_exit_status);
		while (ex_stat[k])
		{
			new_line[*j] = ex_stat[k];
			(*j)++;
			k++;
		}
		free(ex_stat);
	}
	else if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		parse_dollar_value(data, new_line, i, j);
}

static void	parse_tilde(t_data *data, char *newline, int *i, int *j)
{
	char	*home_path;
	int		k;

	if (data->line[*i + 1])
		(*i)++;
	home_path = get_home_path(data);
	k = 0;
	while (home_path && home_path[k])
	{
		newline[*j] = home_path[k];
		(*j)++;
		k++;
	}
	if (home_path)
		free(home_path);
}

static void	parsed_line(t_data *data, char *new_line,
		int *in_singleq, int *in_doubleq)
{
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	while (data->line[++(i[0])])
	{
		if (data->line[i[0]] == ' ' && !(*in_singleq) && !(*in_doubleq))
			parse_spaces(data->line, &i[0]);
		if (data->line[i[0]] == '\\' && !(*in_singleq) && !(*in_doubleq))
			(i[0])++;
		if (data->line[i[0]] == '$' && !(*in_singleq) && (i[0] == 0
				|| data->line[i[0] - 1] != '\\') && data->line[i[0] + 1] != '~')
			parse_dollar_var(data, new_line, &i[0], &i[1]);
		if (data->line[i[0]] == '~' && !(*in_singleq) && !(*in_doubleq)
			&& data->line[i[0] - 1] == ' ' && (data->line[i[0] + 1] == ' '
				|| data->line[i[0] + 1] == '/' || !data->line[i[0] + 1]))
			parse_tilde(data, new_line, &i[0], &i[1]);
		if (data->line[i[0]] == '*' && !(*in_singleq) && !(*in_doubleq)
			&& (i[0] == 0 || data->line[i[0] - 1] != '\\'))
			parse_wildcard(data->line, new_line, &i[0], &i[1]);
		if (parse_conditions(data->line, i[0], *in_singleq, *in_doubleq))
			new_line[(i[1])++] = data->line[i[0]];
		if ((data->line[i[0]] == '\'' || data->line[i[0]] == '\"'))
			in_or_out_quotes(data->line, in_singleq, in_doubleq, i[0]);
	}
}

char	*parse_line(char *line, char **env)
{
	t_data	data;
	char	*new_line;
	int		in_singleq;
	int		in_doubleq;
	int		len;

	data.line = ft_strtrim(line, " ()");
	data.env = env;
	in_singleq = 0;
	in_doubleq = 0;
	data.line = unclosed_quotes(&data);
	free(line);
	len = 0;
	new_line_len(&data, &len, in_singleq, in_doubleq);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	parsed_line(&data, new_line, &in_singleq, &in_doubleq);
	free(data.line);
	return (new_line);
}
