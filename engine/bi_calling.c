#include "../headers/minishell.h"

void exe_built_in(t_parse_lst *lst)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		redir(lst);
		close_pipes(lst);
		if (lst->built_in == e_echo)
			ft_echo(lst);
		else if (lst->built_in == e_pwd)
			ft_pwd(lst);
		else if (lst->built_in == e_cd)
			ft_cd(lst);
		else if (lst->built_in == e_export)
			ft_export(lst); // send only env list
		else if (lst->built_in == e_unset)
			ft_unset(lst); // send only env list
		exit (0);
	}
}