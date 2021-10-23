/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:13:56 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

bool	redir(t_parse_lst *lst)
{
	if (dup2((lst)->fd_in, 0) == -1)
		return (false);
	if (dup2((lst)->fd_out, 1) == -1)
		return (false);
	return (true);
}
