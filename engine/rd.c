#include "../headers/minishell.h"

void io_pipes(t_parse_lst **lst)
{
	// t_parse_lst	*pars_tmp = *lst;
	int	pfd[2];
	if ((*lst)->next && !(*lst)->fd_in)
	{
		pipe (pfd);
		close (pfd[0]);
		(*lst)->fd_in = pfd[1];
	}
	else
		return;
	*lst = (*lst)->next;
	while ((*lst)->next)
	{
		pipe (pfd);
		if ((*lst)->fd_in == 1)
			(*lst)->fd_in = pfd[1];
		if (!(*lst)->fd_out)
			(*lst)->fd_out = pfd[0];
		*lst = (*lst)->next;
	}
}

void	redir(t_parse_lst **lst)
{
	dup2((*lst)->fd_in, 1); // вопрос если меняем  1 на 1
	dup2((*lst)->fd_out, 0);
}