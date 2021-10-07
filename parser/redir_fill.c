/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 00:26:54 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/07 13:39:22 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

int	get_fd_in(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_in;
	t_deviders	*tmp_dev;

	fd_in = -1;
	while ((*dev_lst) && ((*dev_lst)->type == back_redir_is_next \
							|| (*dev_lst)->type == double_back_redir_is_next))
	{
		close(fd_in);
		if ((*dev_lst)->type == back_redir_is_next)
		{
			fd_in = single_redir_fd(str, *dev_lst, (*dev_lst)->type);
			if (fd_in == -1)
				return (-1);
		}
		else
			fd_in = double_redir_fd(str, *dev_lst, true, curr_pars);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		free_dev_lst(&tmp_dev);
		curr_pars->fd_in = fd_in;
	}
	return (1);
}

int	get_fd_out(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_out;
	t_deviders	*tmp_dev;

	fd_out = -1;
	while ((*dev_lst) && ((*dev_lst)->type == redir_is_next || \
						(*dev_lst)->type == double_redir_is_next))
	{
		if (fd_out != -1)
			close(fd_out);
		if ((*dev_lst)->type == redir_is_next)
			fd_out = single_redir_fd(str, *dev_lst, (*dev_lst)->type);
		else
			fd_out = double_redir_fd(str, *dev_lst, false, curr_pars);
		if (curr_pars->fd_in == -1 || fd_out == -1)
			return (-1);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		curr_pars->fd_out = fd_out;
		free_dev_lst(&tmp_dev);
	}
	return (1);
}

int	get_redir_fd(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int	res;

	res = 0;
	while ((*dev_lst) && (*dev_lst)->type != pipe_is_next \
		&& (*dev_lst)->type != none && res != -1)
	{
		if ((*dev_lst)->type == redir_is_next || \
									(*dev_lst)->type == double_redir_is_next)
			res = get_fd_out(curr_pars, dev_lst, str);
		else if ((*dev_lst)->type == back_redir_is_next || \
								(*dev_lst)->type == double_back_redir_is_next)
			res = get_fd_in(curr_pars, dev_lst, str);
	}
	return (res);
}
