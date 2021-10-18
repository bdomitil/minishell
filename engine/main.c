#include "../headers/minishell.h"

static void wait_function(t_parse_lst *lst)
{
	int status;

	while (lst)
	{
		waitpid(lst->pid, &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
//			printf("here\n");
//			exit(errno);
		}
		lst = lst->next;
	}
}

void	my_exit(char *welc)
{
	int			i;

	i = 18 + rl_end;
	printf("\e[A");
	while (i--)
		printf("\e[C");
	printf("exit\n");
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	char *str;
	t_parse_lst *lst = NULL;
	t_parse_lst *head = NULL;
	t_env		*env_lst;

	(void)argc, (void)argv;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	env_lst = parse_env(env);
	while ((str = readline("mini$heeee$h-1.0$ ")))
	{
		if (!str)
			exit(0);
		if (ft_strcmp(str, "\0"))
			add_history(str);
		errno = 0;
		if (parser(&str, &lst, env_lst) == -1)
		{
			printf("\n\n______ERROR______\n\n");
			continue;
		}
//				print_pars_lst(&lst);  //delete it later
		if (lst)
		{
			head = lst->head;
			io_pipes(lst);
			while (lst)
			{
				if (lst->built_in)
				{
					if (lst->next || lst->previous)
					{
						signal(SIGINT, ctrl_c_forked);
						builtin_fork_call(lst);
					}
					else
						builtin_unar_call(lst);
				}
				else
				{
					signal(SIGINT, ctrl_c_forked);
					exex(&lst);
				}
				lst = lst->next;
			}
			lst = head;
			close_pipes(lst);
			wait_function(lst);
			signal(SIGINT, ctrl_c);
			rm_here_docs(env, lst);
			clean_main_list(lst);
			lst = NULL;
			}
		}
		return 0;
}