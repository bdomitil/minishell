#include "../headers/minishell.h"


bool	redir(t_parse_lst *lst)
{
	if (dup2((lst)->fd_in, 0) == -1)
	{
		error_sh_cmd_msg(1, "dup2", NULL, strerror(errno));
		return (false);
	}
	if (dup2((lst)->fd_out, 1) == -1)
	{
		error_sh_cmd_msg(1, "dup2", NULL, strerror(errno));
		return (false);
	}
	return (true);
}