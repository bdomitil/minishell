/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_calling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:52:20 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 13:53:43 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	choose_func(t_parse_lst *lst)
{
	if (lst->built_in == e_echo)
		ft_echo(lst);
	else if (lst->built_in == e_pwd)
		ft_pwd(lst);
	else if (lst->built_in == e_cd)
		ft_cd(lst);
	else if (lst->built_in == e_export)
		ft_export(lst);
	else if (lst->built_in == e_unset)
		ft_unset(lst);
	else if (lst->built_in == e_env)
		ft_env(lst->env_lst);
	else if (lst->built_in == e_exit)
		ft_exit(lst);
}

void	builtin_unar_call(t_parse_lst *lst)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	if (!redir(lst))
		return ;
	if (! close_fds(lst))
		return ;
	choose_func(lst);
	if (dup2(fd_in, 0) == -1)
	{
		error_sh_cmd_msg(1, "close", NULL, strerror(errno));
		return ;
	}
	if (dup2(fd_out, 1) == -1)
	{
		error_sh_cmd_msg(1, "close", NULL, strerror(errno));
		return ;
	}
	close (fd_in);
	close (fd_out);
}

void	builtin_fork_call(t_parse_lst *lst)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (!redir(lst))
			exit(-1);
		if (!close_fds(lst))
			exit (-1);
		choose_func(lst);
		exit (0);
	}
	else
		lst->pid = pid;
}
