/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:19:47 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/06 14:36:57 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Creates a new node for a list and sets is content.
*/
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

/*
 *	Returns the last node of a list.
*/
t_export	*lst_get_last(t_export *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

/*
 *	Inserts a node at the end of a list.
*/
void	lst_add_back(t_export **lst, t_export *new)
{
	t_export	*last;

	last = lst_get_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
