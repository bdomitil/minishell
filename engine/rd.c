#include "../headers/minishell.h"


void	redir(t_parse_lst *lst)
{
	dup2((lst)->fd_in, 0);
	dup2((lst)->fd_out, 1);
}