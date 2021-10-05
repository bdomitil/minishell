#include "../headers/minishell.h"

void	get_fd_of_hd(t_parse_lst *lst)
{
	int	pfd[2];
	int	pid;

	pipe(pfd);
	lst->fd_out = pfd[1];
	pid = fork();
	if (!pid)
	{
		close_pipes(lst);
		close(pfd[0]);
		while (*lst->here_doc)
		{
			write(pfd[1], *lst->here_doc, ft_strlen(*lst->here_doc));
			write(pfd[1], "\n", 1);
			lst->here_doc++;
		}
		exit (0);
	}
	else
	{
		dup2(lst->fd_out, 0); //  вопрос
		close (pfd[0]), close(pfd[1]);
	}
}

void	redir(t_parse_lst **lst)
{
	dup2((*lst)->fd_in, 1);
	dup2((*lst)->fd_out, 0);
}