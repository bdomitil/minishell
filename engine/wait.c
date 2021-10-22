#include "../headers/minishell.h"

bool wait_process(t_parse_lst *lst)
{
	int	status;

	if (lst->pid == 0)
		return (true);
	waitpid(lst->pid, &status, 0);
	if (WEXITSTATUS(status))
	{
		if (status == 512)
		{
			printf("status = %d\n" , status);
			if (lst->command)
				error_sh_cmd_msg(1, lst->command, NULL, "command not found");
			g_exit_status = 1;
			return (false);
		}
		else
		{
			g_exit_status = 1;
			return (false);
		}
	}
	if (WIFSIGNALED(status) != 0)
		g_exit_status = 128 + status;
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