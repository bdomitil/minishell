#include "../headers/minishell.h"

static void wait_function(t_parse_lst *lst)
{
	int status;

	while (lst)
	{
		waitpid(lst->pid, &status, 0);
		g_exit_status = 0;
		if (WIFEXITED(status))
		{
			if (status)
				g_exit_status = 1;
		}
		if (WIFSIGNALED(status) != 0)
			g_exit_status = 128 + status;
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
	env_lst = parse_env(env);
	while ((str = readline("mini$heeee$h-1.0$ ")))
	{
		if (!str)
			exit(0);
		if (ft_strcmp(str, "\0"))
			add_history(str);
		else
			g_exit_status = 0;
		errno = 0;
		if (parser(&str, &lst, env_lst) == -1)

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
					signal(SIGQUIT, ctrl_slsh);
					signal(SIGINT, ctrl_c_forked);
					exex(&lst);
				}
				lst = lst->next;
			}
			lst = head;
			close_pipes(lst);
			wait_function(lst);
			signal(SIGINT, ctrl_c);
			signal(SIGQUIT, SIG_IGN);
			rm_here_docs(env, lst);
			clean_main_list(lst);
			lst = NULL;
		}
	}
	return 0;
}
