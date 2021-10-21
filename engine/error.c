#include "../headers/minishell.h"

void error_sh_cmd_msg(int exit_status, char *cmd, char *arg, char *message)
{
	ft_putstr_fd("mini$heeee$h: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = exit_status;
}
