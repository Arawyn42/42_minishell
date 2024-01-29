/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:14 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 22:46:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Converts a string into an int and returns it.
*/
int	ft_atoi(const char *s)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

/*
 *	Calculates the length of the result string for the ft_itoa function.
*/
static int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 0)
	{
		n = n / 10;
		i++;
		if (n == 0)
			break ;
	}
	return (i);
}

/*
 *	Converts an int into a string and returns it.
*/
char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	int		len;

	nb = (long) n;
	len = ft_len(nb);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (nb < 0)
	{
		nb = -nb;
		res[0] = '-';
	}
	while (nb >= 0)
	{
		res[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
		if (nb == 0)
			break ;
	}
	return (res);
}
