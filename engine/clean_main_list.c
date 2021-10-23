/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_main_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:58:03 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 13:58:47 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	t_lst_clear(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		free (tmp->content);
		tmp->content = NULL;
		free (tmp);
		tmp = NULL;
		lst = lst->next;
	}
}

static void	clear_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args;
		free (tmp->arg);
		tmp->arg = NULL;
		free (tmp);
		tmp = NULL;
		args = args->next;
	}
}

void	clean_main_list(t_parse_lst *lst)
{
	t_parse_lst	*tmp;

	tmp = lst;
	if (tmp && tmp->args)
		clear_args(tmp->args);
	if (tmp && tmp->stop_list)
		t_lst_clear(tmp->stop_list);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->command);
		tmp->command = NULL;
	}
}
