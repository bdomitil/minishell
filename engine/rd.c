#include "../headers/minishell.h"


bool	redir(t_parse_lst *lst)
{
	if (dup2((lst)->fd_in, 0) == -1)
		return (false);
	if (dup2((lst)->fd_out, 1) == -1)
		return (false);
	return (true);
}