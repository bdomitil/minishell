/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:16:02 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

void	ctrl_c(int signal)
{
	int	k;

	g_mshl.g_exit_status = 1;
	k = rl_end + 18;
	if (signal == SIGINT)
	{
		while (k--)
			printf("\e[C");
		printf("\e[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_c_forked(int signal)
{
	int	k;

	k = rl_end + 18;
	if (signal == SIGINT)
	{
		while (k--)
			printf("\e[C");
		printf("\e[K\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_slsh(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit: 3\n");
}

void	ctrl_c_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_mshl.hd_return = 0;
		g_mshl.g_exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
