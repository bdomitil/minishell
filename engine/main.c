#include "../headers/minishell.h"

static void wait_function(t_parse_lst *lst)
{
	while (lst)
	{
		wait_hd(lst->pid); // мб сломается все
		lst = lst->next;
	}
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
	if (env)
		env_lst = parse_env(env);
	while ((str = readline("mini$heeee$h-1.0$ ")))
	{
		if (!str)
			exit(0);
		if (ft_strcmp(str, "\0"))
			add_history(str);
		else
			g_exit_status = 0;
		printf("res  = %d\n",parser(&str, &lst, env_lst));
		print_pars_lst(&lst); //delete it later
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
						signal(SIGINT, ctrl_c_forked); // ват
						builtin_fork_call(lst);
					}
					else
					{
						builtin_unar_call(lst);
						printf("g_exit_st %d\n", g_exit_status);
//						error_sh_cmd_msg(1, "export", NULL, "not a valid identifier");
					}
				}
				else
				{
					signal(SIGQUIT, ctrl_slsh);
					signal(SIGINT, ctrl_c_forked);
					exex(&lst);
				}
				lst = lst->next;
			}
			lst = head;
			close_fds(lst); // при ошибке закрытия будет ждать процессов и будет жить дальше. вопрос: стоит ли ему дальше жить
			wait_function(lst);
			signal(SIGINT, ctrl_c);
			signal(SIGQUIT, SIG_IGN);
//			rm_here_docs(env, lst);
			clean_main_list(lst);
			lst = NULL;
		}
	}
	return 0;
}
