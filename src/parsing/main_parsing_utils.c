/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:34:30 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/05 17:38:08 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_file(char **command, int i)
{
	if (!command[i - 1])
		return (0);
	if (ft_strchr("><", command[i - 1][0]))
		return (1);
	return (0);
}

char	**parse_command(char **command, char **env)
{
	int		i;

	if (!command)
		return (NULL);
	i = 1;
	while (command[i])
	{
		command[i] = parse_line(command[i], env, 0);
		i++;
	}
	return (command);
}

char	*trim_one(char *src, char *charset)
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

char	**trim_command(char **command, char *charset)
{
	char	*tmp;
	int		i;

	if (!command)
		return (NULL);
	i = 1;
	while (command[i])
	{
		tmp = trim_one(command[i], charset);
		free(command[i]);
		command[i] = tmp;
		i++;
	}
	return (command);
}
