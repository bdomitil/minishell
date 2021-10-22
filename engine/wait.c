#include "../headers/minishell.h"

bool wait_process(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_exit_status = 0;
	if (WIFEXITED(status))
		if (status)
		{
			g_exit_status = 1;
			return (false);
		}
	if (WIFSIGNALED(status) != 0)
		g_exit_status = 128 + status;
	return (true);
}

void while_wait(t_parse_lst *lst)
{
	while (lst)
	{
		wait_process(lst->pid); // мб сломается все
		lst = lst->next;
	}
}

