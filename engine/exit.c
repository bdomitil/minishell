#include "../headers/minishell.h"

void ft_exit(t_parse_lst *lst) // return value?
{
	int	arg;

	if (lst->args)
	{
		if (!ft_all_numeric(lst->args->arg))
			exit(0);
		if (lst->args->next)
		{
			printf("exit: too many arguments\n");
			return ;
		}
		arg = ft_atoi(lst->args->arg);
		arg %= 255;
		exit (arg);
	}
	exit (g_exit_status);
}