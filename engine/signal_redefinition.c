/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_redefinition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:14:35 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 17:51:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	parent_sign_redif(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	exex_sign_redif(void)
{
	signal(SIGQUIT, ctrl_slsh);
	signal(SIGINT, ctrl_c_forked);
}

void	hd_sig_redif(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_heredoc);
}
