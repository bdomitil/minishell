/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:45:07 by bdomitil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/23 19:13:52 by bdomitil         ###   ########.fr       */
=======
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
>>>>>>> a03602387d6ae795c9bbcac6fa4a10cce1f57644
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

void	exit_print(t_parse_lst **lst, bool parse_error)
{
	if (parse_error && errno != 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		g_mshl.g_exit_status = parse_error;
		clean_main_list(*lst);
		return ;
	}
	close_fds(*lst);
	while_wait(*lst);
	clean_main_list(*lst);
	free(*lst);
	*lst = NULL;
	parent_sign_redif();
}
