/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:24:25 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

static int	hd_readline(int *pfd, t_list *tmp)
{
	char	*line;

	line = readline("> ");
	if (!g_mshl.hd_return)
	{
		free(line);
		return (3);
	}
	if (!ft_strcmp(line, (char *) tmp->content) || !line)
	{
		free(line);
		return (0);
	}
	if (!tmp->next)
	{
		write(pfd[1], line, ft_strlen(line));
		free(line);
		write(pfd[1], "\n", 1);
	}
	return (1);
}

static void	child_hd(int *pfd, t_parse_lst *lst)
{
	int		res;
	t_list	*tmp;

	tmp = lst->stop_list;
	close (pfd[0]);
	while (tmp)
	{
		while (1)
		{
			res = hd_readline(pfd, tmp);
			if (!res)
				break ;
			else if (res == 3)
				exit(-1);
		}
		tmp = tmp->next;
	}
	write(pfd[1], (void *)EOF, 4);
	close (pfd[1]);
	exit(0);
}

bool	hd_exec(t_parse_lst *lst, int *pfd)
{
	pid_t	pid;

	g_mshl.hd_return = 1;
	if (pipe(pfd) == -1)
	{
		error_sh_cmd_msg(1, "pipe", NULL, strerror(errno));
		return (false);
	}
	pid = fork();
	hd_sig_redif();
	if (pid == -1)
	{
		error_sh_cmd_msg(1, "fork", NULL, strerror(errno));
		return (false);
	}
	if (!pid)
		child_hd(pfd, lst);
	lst->pid = pid;
	if (!wait_process(lst))
		return (false);
	close(pfd[1]);
	lst->fd_in = pfd[0];
	return (true);
}

bool	here_doc(t_parse_lst *lst, t_exec_args *tmp)
{
	int	pfd[2];

	if (lst->fd_in != -2)
		return (true);
	if (!hd_exec(lst, pfd))
	{
		freesh(tmp);
		g_mshl.g_exit_status = 1;
		return (false);
	}
	return (true);
}
