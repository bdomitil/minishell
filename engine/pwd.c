/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:08:05 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 21:26:20 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		error_sh_cmd_msg(1, "pwd", NULL, strerror(errno));
		return ;
	}
	write (1, str, ft_strlen(str));
	free (str);
	write(1, "\n", 1);
	write(1, (void *)EOF, 4);
	g_mshl.g_exit_status = 0;
}
