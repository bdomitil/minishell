#include "../headers/parse.h"

t_args	*init_arg_lst(void)
{
	t_args *args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->next = NULL;
	args->previous = NULL;
	args->head = NULL;
	args->tail = NULL;
	args->arg = NULL;
	return (args);
}

t_parse_lst	*init_pars_lst(void)
{
	t_parse_lst *lst;

	lst = malloc(sizeof(t_parse_lst));
	if (!lst)
		return (NULL);
	lst->head = lst;
	lst->tail = lst;
	lst->next = NULL;
	lst->previous = NULL;
	lst->args = NULL;
	lst->pipe = false;
	lst->stop_word = NULL;
	lst->fd_in = 0;
	lst->fd_out = 0;
	lst->exit_status = 0;
	lst->command = NULL;
	return (lst);
}

