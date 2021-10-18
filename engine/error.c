#include "../headers/minishell.h"

int error_sh_cmd_msg(int exit_status, char *cmd, char *message)
{
	g_exit_status = exit_status;
	ft_putstr_fd("mini$heeee$h: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}