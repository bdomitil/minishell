#include "../headers/minishell.h"

static void wait_function(t_parse_lst *lst)
{
	int status;

	while (lst)
	{
		waitpid(lst->pid, &status, 0);
		g_exit_status = 0;
		if (WIFEXITED(status))
			if (status)
				g_exit_status = 1;
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
//		errno = 0;
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
					{
						signal(SIGINT, ctrl_c_forked);
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

void error_sh_cmd_msg(int exit_status, char *cmd, char *arg, char *message)
{
	printf("ex-st %d\n", exit_status);
	ft_putstr_fd("mini$heeee$h: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = exit_status;
	printf("2ex-st %d\n", exit_status);
}
