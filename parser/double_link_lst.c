/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_link_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:14:51 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 16:14:52 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

void	ft_shell_lst_add_back(t_parse_lst *lst, t_parse_lst *new)
{
	if (!lst)
	{
		lst = new;
		return ;
	}
	if (!lst->next)
	{
		lst->next = new;
		lst->head = lst;
		lst->tail = new;
		new->previous = lst;
		return ;
	}
	new->head = lst;
	while (lst->next)
	{
		lst->tail = new;
		lst = lst->next;
	}
	new->previous = lst;
	lst->tail = new;
	lst->next = new;
	return ;
}

void	ft_args_lst_add_back(t_parse_lst *lst, t_args *new)
{
	t_args	*temp;

	temp = lst->args;
	if (!lst->args)
	{
		lst->args = new;
		new->next = NULL;
		new->head = new;
		new->tail = new;
		return ;
	}
	new->head = lst->args;
	while (temp->next)
	{
		temp->tail = new;
		temp = temp->next;
	}
	new->id = temp->id + 1;
	new->previous = temp;
	temp->tail = new;
	temp->next = new;
	return ;
}
