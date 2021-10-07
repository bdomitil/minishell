#include "../headers/minishell.h"

static void ftecho(t_parse_lst *lst)
{
	if (!ft_strncmp("-n\0", lst->args->head->arg, 3) && lst->args->next)
		lst->args = lst->args->next;
	while (lst->args)
	{
		write(1, lst->args->arg, ft_strlen(lst->args->arg));
		lst->args = lst->args->next;
	}
	if (ft_strncmp("-n\0", lst->args->head->arg, 3))
		write(1, "\n", 1);
	write(1, (void *)EOF, 4); // может ломать
}

void exe_built_in(t_parse_lst *lst)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		redir(lst);
		close_pipes(lst);
		if (lst->built_in == ft_echo)
			ftecho(lst);
		exit (0);
	}

}
