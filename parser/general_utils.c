/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:15:28 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/07 13:39:22 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_args	*init_arg_lst(char *str)
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
	args->arg = str;
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
	lst->stop_list = NULL;
	lst->built_in = 0;
	lst->fd_out = 1;
	lst->fd_in = 0;
	lst->exit_status = 0;
	lst->command = NULL;
	lst->here_doc = NULL;
	return (lst);
}
