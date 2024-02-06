/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:34:30 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/06 14:40:48 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 *	Returns 1 if the string in the position i in the array command is
 *	supposed to be a file. Returns 0 otherwise.
 *	Note : i has to be superior or egual to 1.
*/
int	is_file(char **command, int i)
{
	if (!command[i - 1])
		return (0);
	if (ft_strchr("><", command[i - 1][0]))
		return (1);
	return (0);
}

/*
 *	Delete the first and the last character from the string if theses
 *	characters are found in the charset.
 *	Returns the new trimmed string.
*/
static char	*trim_one(char *src, char *charset)
{
	char	*ret;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	len = ft_strlen(src);
	if (src[0] == src[len - 1] && ft_strchr(charset, src[0]))
	{
		ret = ft_calloc(len - 1, sizeof(char));
		i = 1;
		len--;
	}
	else
	{
		ret = ft_calloc(len + 1, sizeof(char));
		i = 0;
	}
	while (i < len)
	{
		ret[j] = src[i];
		i++;
		j++;
	}
	return (ret);
}

/*
 *	Applies the famous function parse_line on each strings of the array command.
*/
char	**parse_command(char **command, char **env)
{
	int		i;
	char	*tmp;

	if (!command)
		return (NULL);
	i = 1;
	while (command[i])
	{
		if (i == 1 || ft_strncmp(command[i - 1], "<<", 2))
			command[i] = parse_line(command[i], env, 0);
		else
		{
			tmp = trim_one(unclosed_quotes(command[i]), "\'\"");
			free(command[i]);
			command[i] = tmp;
		}
		i++;
	}
	return (command);
}

/*
 *	Delete the first and the last character from all the string of the array
 *	command if theses characters are found in the charset.
 *	Returns the new trimmed command array.
*/
char	**trim_command(char **command, char *charset)
{
	char	*tmp;
	int		i;

	if (!command)
		return (NULL);
	i = 0;
	while (command[i])
	{
		tmp = trim_one(command[i], charset);
		free(command[i]);
		command[i] = tmp;
		i++;
	}
	return (command);
}
