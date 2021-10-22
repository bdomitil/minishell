#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	// char *str = ft_strdup(">");
	char *str;
	t_parse_lst *lst = NULL;
	t_parse_lst *head = NULL;
	t_env		*env_lst;

	(void)argc, (void)argv;
	if (env)
		env_lst = parse_env(env);
	parent_sign_redif();
	while ((str = readline("mini$heeee$h-1.0$ ")))
	{

		if (!str)
		{
			exit(1);
		}
		if (ft_strcmp(str, "\0"))
			add_history(str);
		else
			g_exit_status = 0;
		parser(&str, &lst, env_lst);
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
					{// ват
						builtin_fork_call(lst);
					}
					else
						builtin_unar_call(lst);
				}
				else
				{
					exex_sign_redif();
					exex(&lst);
					parent_sign_redif();
				}
				lst = lst->next;
			}
			lst = head;
			close_fds(lst); // при ошибке закрытия будет ждать процессов и будет жить дальше. вопрос: стоит ли ему дальше жить
			while_wait(lst);
			clean_main_list(lst);
			lst = NULL;
			parent_sign_redif();
		}
	}
	return 0;
}
