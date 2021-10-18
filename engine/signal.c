#include "../headers/minishell.h"

void	ctrl_c(int signal)
{
	int			k;

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
