#include "../headers/minishell.h"

void io_pipes(t_parse_lst *lst)
{
	int	pfd[2];

	printf("1here\n");
	while (lst)
	{
		pipe (pfd);
//		printf("fdIN before %d\n", lst->fd_in); // !
		if ((lst)->fd_in == 1 && (lst)->next)
		{
			(lst)->fd_in = pfd[1];
		}
		if (!lst->previous)
			close (pfd[0]);
//		printf("fdIN after %d\n", lst->fd_in); // !
//		printf("fdOUT bef %d\n", lst->fd_out); // !
		if (!(lst)->fd_out && (lst)->previous)
			(lst)->fd_out = pfd[0];
		if (!(lst)->next && lst->previous)
			close(pfd[1]);
//		printf("fdOUT after %d\n", lst->fd_out); // !

		lst = (lst)->next;
	}

}

void	redir(t_parse_lst **lst)
{
	dup2((*lst)->fd_in, 1);
	dup2((*lst)->fd_out, 0);
}