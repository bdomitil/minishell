/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:13:23 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

void	ft_exit(t_parse_lst *lst)
{
	int	arg;

	ft_putendl_fd("exit", 2);
	if (lst->args)
	{
		if (!ft_all_numeric(lst->args->arg) || ft_strlen(lst->args->arg) > 11)
			error_sh_cmd_msg(255, "exit", lst->args->arg, \
			"numeric argument required");
		else
		{
			if (lst->args->next)
			{
				error_sh_cmd_msg(1, "exit", NULL, "too many arguments");
				return ;
			}
			arg = ft_atoi(lst->args->arg);
			if (arg > 255 || arg < 0)
				g_mshl.g_exit_status = arg % 256;
			else
				g_mshl.g_exit_status = arg;
		}
	}
	exit (g_mshl.g_exit_status);
}
