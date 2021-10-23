#include "../headers/minishell.h"

bool wait_process(t_parse_lst *lst)
{
	int	status;

	if (lst->pid == 0)
		return (true);
	waitpid(lst->pid, &status, 0);
	if (!lst->next)
	{
		g_mshl.g_exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) != 0)
		g_mshl.g_exit_status = 128 + status;
	return (true);
}

void while_wait(t_parse_lst *lst)
{
	while (lst)
	{
		wait_process(lst); // мб сломается все
		lst = lst->next;
	}
}