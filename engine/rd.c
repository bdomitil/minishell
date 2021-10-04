#include "../headers/minishell.h"

void io_pipes(t_parse_lst *lst)
{
	int	pfd[2];

	while (lst)
	{
		pipe (pfd);
		printf("pipe fds:\tread: %d\twrite: %d\n", pfd[0], pfd[1]);
		printf("lst cmd %s\tfdIN before %d\n", lst->command, lst->fd_in);

		if ((lst)->fd_in == 1 && (lst)->next)
		{
			(lst)->fd_in = pfd[1];
		}
//		if (!lst->previous)
//			close (pfd[0]); // МБ ДЕЛИД
		printf("lst cmd %s\tfdIN AFTER %d\n", lst->command, lst->fd_in); // !
		printf("lst cmd %s\tfdOUT BEF %d\n", lst->command, lst->fd_out); // !
		if ((lst)->next && !(lst)->next->fd_out)
			(lst)->next->fd_out = pfd[0];
//		if (!(lst)->next && lst->previous)
//			close(pfd[1]);
		printf("lst cmd %s\tfdOUT AFTER %d\n", lst->command, lst->fd_out); // !

		lst = (lst)->next;
		printf("\n_________________\n");
	}

}

void	redir(t_parse_lst **lst)
{
	dup2((*lst)->fd_in, 1);
	dup2((*lst)->fd_out, 0);
}