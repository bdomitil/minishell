#include "../headers/minishell.h"

void	ctrl_c(int signal)
{
	int			k;

	g_exit_status = 1;
	k = rl_end + 18;
	if (signal == SIGINT)
	{
		while (k--)
			printf("\e[C");
		printf("\e[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_c_forked(int signal)
{
	int			k;

	k = rl_end + 18;
	if (signal == SIGINT)
	{
		while (k--)
			printf("\e[C");
		printf("\e[K\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	ctrl_d(int signal)
{
	int			i;

	//	i = 18 + rl_end;
	printf("\e[A");
	while (i--)
		printf("\e[C");
	printf("\nexit\n");
	exit(g_exit_status);
}

void ctrl_slsh(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit: 3\n");
}