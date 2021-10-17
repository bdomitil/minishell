#include "../headers/minishell.h"

void	io_pipes(t_parse_lst *lst) // rename
{
	int			pfd[2];
	char		a[1];
	t_parse_lst	*tmp;


	tmp = lst;

	a[0] = 1;
	if (tmp->fd_in == -2)
	{
		tmp->fd_in = hd(tmp, a);
		a[0]++;
	}
	if (!tmp->next)
		return;
	else
	{
		pipe (pfd);
		if (tmp->fd_out != 1)
			close (pfd[1]);
		if (tmp->fd_out == 1 && (tmp)->next)
			(tmp)->fd_out = pfd[1];
		if (!tmp->next)
			close (pfd[1]);
		if (!tmp->next)
			close (pfd[0]);
		if (tmp->next && tmp->next->fd_in == 0 && tmp->next->fd_in != -2)
			tmp->next->fd_in = pfd[0];
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->fd_in == -2)
		{
			tmp->fd_in = hd(tmp, a);
			a[0]++;
		}
		pipe (pfd);
		if (tmp->fd_out != 1)
			close (pfd[1]);
		if ((tmp)->fd_out == 1 && (tmp)->next)
			(tmp)->fd_out = pfd[1];
		if (!tmp->next)
		{
			close (pfd[1]);
			close (pfd[0]);
		}
		if (tmp->next && tmp->next->fd_in == 0 && tmp->next->fd_in != -2)
			(tmp)->next->fd_in = pfd[0];
		tmp = (tmp)->next;
	}
}

void close_pipes(t_parse_lst *lst) // close fds
{
	t_parse_lst *tmp_lst;

	tmp_lst = lst->head;
	while (tmp_lst)
	{
	    if (tmp_lst->fd_out != 1)
	        close (tmp_lst->fd_out);
	    if (tmp_lst->fd_in != 0)
	        close (tmp_lst->fd_in);
		tmp_lst = tmp_lst->next;
	}
}