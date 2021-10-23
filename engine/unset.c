/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:16:21 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 17:16:22 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_unset(t_parse_lst *lst)
{
	t_args	*tmp_arg;

	tmp_arg = lst->args;
	while (tmp_arg)
	{
		del_env_lst_by_key(lst->env_lst, tmp_arg->arg);
		tmp_arg = tmp_arg->next;
	}
}
