/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:19:47 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/11 22:20:16 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*lst_new_node(char *content)
{
	t_export	*res;

	res = (t_export *)malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}

void	lst_add_front(t_export **lst, t_export *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

t_export	*lst_get_last(t_export *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	lst_add_back(t_export **lst, t_export *new)
{
	t_export	*last;

	last = lst_get_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
