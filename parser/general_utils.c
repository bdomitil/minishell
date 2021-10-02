/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nastya <nastya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:15:28 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/27 21:22:23 by nastya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_args	*init_arg_lst(void)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->next = NULL;
	args->previous = NULL;
	args->head = NULL;
	args->tail = args;
	args->id = 0;
	args->arg = NULL;
	return (args);
}

t_parse_lst	*init_pars_lst(void)
{
	t_parse_lst	*lst;

	lst = malloc(sizeof(t_parse_lst));
	if (!lst)
		return (NULL);
	lst->head = lst;
	lst->tail = lst;
	lst->next = NULL;
	lst->previous = NULL;
	lst->args = NULL;
	lst->pipe = false;
	lst->stop_word = NULL;
	lst->fd_in = 1;
	lst->fd_out = 0;
	lst->exit_status = 0;
	lst->command = NULL;
	return (lst);
}
