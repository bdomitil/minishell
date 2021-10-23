#include "../headers/minishell.h"

void	io_pipes(t_parse_lst *lst)
{
	int			pfd[2];
	char		a[1];
	t_parse_lst	*tmp;


	tmp = lst;

	a[0] = 1;
	if (!tmp->next)
		return;
	while (tmp)
	{
		pipe (pfd);
		if (tmp->fd_out != 1)
			close (pfd[1]);
		if (tmp->fd_out == 1 && tmp->next)
			tmp->fd_out = pfd[1];
		if (!tmp->next)
		{
			close (pfd[1]);
			close (pfd[0]);
		}
		if (tmp->next && tmp->next->fd_in == 0 && tmp->next->fd_in != -2)
			tmp->next->fd_in = pfd[0];
		tmp = (tmp)->next;
	}
}

bool close_fds(t_parse_lst *lst)
{
	t_parse_lst *tmp_lst;

	tmp_lst = lst->head;
	while (tmp_lst)
	{
	    if (tmp_lst->fd_out != 1)
	        if (close (tmp_lst->fd_out) == -1)
				return (false);
	    if (tmp_lst->fd_in != 0 && tmp_lst->fd_in != -2)
	    	if (close (tmp_lst->fd_in) == -1)
				return (false);
		tmp_lst = tmp_lst->next;
	}
	return (true);
}