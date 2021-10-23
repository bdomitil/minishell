#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	// char *str = ft_strdup("> 3");
	char *str;
	t_parse_lst *lst = NULL;
	t_parse_lst *head = NULL;
	t_env		*env_lst;

	(void)argc, (void)argv;
	if (env)
		env_lst = parse_env(env);
	parent_sign_redif();
	g_exit_status = 0;
	while ((str = readline("mini$heeee$h-1.0$ ")))
	{
		if (ft_strcmp(str, "\0"))
			add_history(str);
		if (parser(&str, &lst, env_lst) == -1)
				exit_print(&lst, true);
		else if (lst)
		{
			print_pars_lst(&lst);
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
						builtin_unar_call(lst);
				}
				else
				{
					exex_sign_redif();
					exex(&lst);
				}
				lst = lst->next;
			}
			lst = head;
			exit_print(&lst, false);
		}
	}
	return 0;
}
