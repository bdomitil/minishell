#include "../headers/minishell.h"

void	io_pipes(t_parse_lst *lst)
{
	int	pfd[2];

	if (lst->fd_out == -2)
	{
		hd(lst);
	}
	if (!lst->next)
		return;
	else
		lst = lst->next;
	while (lst)
	{
		if (lst->fd_out == -2)
			hd(lst);
		pipe (pfd);
		if ((lst)->fd_in == 1 && (lst)->next)
			(lst)->fd_in = pfd[1];
		if ((lst)->next && !(lst)->next->fd_out)
			(lst)->next->fd_out = pfd[0];
		lst = (lst)->next;
	}
}

void close_pipes(t_parse_lst *lst) // close fds
{
	t_parse_lst *tmp_lst;

	tmp_lst = lst;
	while (lst)
	{
	    if (lst->fd_in != 1)
	        close (lst->fd_in);
	    if (lst->fd_out != 0)
	        close (lst->fd_out);
		lst = lst->next;
	}
	lst = tmp_lst;
	while (lst)
	{
	    if (lst->fd_in != 1)
	        close (lst->fd_in);
	    if (lst->fd_out != 0)
	        close (lst->fd_out);
		lst = lst->previous;
	}
}