#include "../headers/minishell.h"

void io_pipes(t_parse_lst *lst)
{
	int	pfd[2];

	while (lst)
	{
		pipe (pfd);
		if ((lst)->fd_in == 1 && (lst)->next)
			(lst)->fd_in = pfd[1];
		if ((lst)->next && !(lst)->next->fd_out)
			(lst)->next->fd_out = pfd[0];
		lst = (lst)->next;
	}
}

void	redir(t_parse_lst **lst)
{
	dup2((*lst)->fd_in, 1);
	dup2((*lst)->fd_out, 0);
}