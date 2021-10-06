#include "../headers/minishell.h"


void	redir(t_parse_lst **lst)
{
	if (!(*lst)->here_doc)
		dup2((*lst)->fd_out, 0);
	dup2((*lst)->fd_in, 1);
}