#include "../headers/minishell.h"

void ft_exit(t_parse_lst *lst) // return value?
{
	int	arg;

	printf ("exit\n");
	if (lst->args)
	{
		if (!ft_all_numeric(lst->args->arg))
			error_sh_cmd_msg(255, "exit", lst->args->arg, "numeric argument required");
		else
		{
			if (lst->args->next)
			{
				error_sh_cmd_msg(1, "exit", NULL, "too many arguments");
				return;
			}
			arg = ft_atoi(lst->args->arg);
			if (arg < 256)
				g_exit_status = arg % 256;
			else
				g_exit_status = arg;
		}
	}
	exit (g_exit_status);
}