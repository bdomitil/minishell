/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:45:07 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 00:11:36 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void exit_print(t_parse_lst **lst, bool parse_error)
{
	if (parse_error && errno != 0)
	{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			g_exit_status = parse_error;
			clean_main_list(*lst);
			return ;
	}
	close_fds(*lst); // при ошибке закрытия будет ждать процессов и будет жить дальше. вопрос: стоит ли ему дальше жить
	while_wait(*lst);
	// if (g_exit_status != 0)
	// {
	// 		write(2, strerror(errno), ft_strlen(strerror(errno)));
	// 		write(2, "\n", 1);
	// }
	clean_main_list(*lst);
	*lst = NULL;
	parent_sign_redif();
}