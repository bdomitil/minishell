#include "../headers/minishell.h"

static void t_lst_clear(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free (tmp->content);
		tmp->content = NULL;
		free (tmp);
		tmp = NULL;
	}
}
// close fd

static void	clear_args(t_args *args)
{
	t_args	*tmp;
	while (args)
	{
		tmp = args;
		args = args->next;
		free (tmp->arg);
		tmp->arg = NULL;
		free (tmp);
		tmp = NULL;
	}
}

void	clean_main_list(t_parse_lst *lst)
{
	t_parse_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->command);
		tmp->command = NULL;
		t_lst_clear(tmp->stop_list);
		clear_args(tmp->args);
// free env list
	}
}