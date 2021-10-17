#include "../headers/minishell.h"


void	redir(t_parse_lst *lst)
{
	if (dup2((lst)->fd_in, 0) == -1)
		terminate(strerror(errno));
	if (dup2((lst)->fd_out, 1) == -1)
		terminate(strerror(errno));
}