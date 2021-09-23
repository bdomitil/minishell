#include "../headers/parse.h"


void print_pars_lst(t_parse_lst **lst)
{
	int i = 1;
	t_parse_lst *pars_tmp = *lst;
	int size = ft_strlen("|command = ||%s||  \
		pipe = ||%d|| \
		redir_in = ||%d|| \
		redir_out = ||%d|| \
		stop_word = ||%s|| \n");
	t_args		*arg_temp;
	printf("\n|_______________________________________________|\n");
	printf("|                                               |\n");
	while (pars_tmp)
	{
		if (pars_tmp != *lst)
			printf("\n _______________________________________________\n");
		arg_temp = pars_tmp->args;

		printf("|command = ||%s||  \
		pipe = ||%d|| \
		redir_in = ||%d|| \
		redir_out = ||%d|| \
		stop_word = ||%s|| \n",
		 pars_tmp->command, \
		 pars_tmp->pipe, \
		pars_tmp->fd_in, \
		pars_tmp->fd_out, \
		pars_tmp->stop_word);
		while (arg_temp)
		{
			printf("|%d arg = ||%s||\n", i, arg_temp->arg);
			arg_temp = arg_temp->next;
			i++;
		}
		pars_tmp = pars_tmp->next;
		printf("|                                               |\n");
		printf("|_______________________________________________|\n\n");
		i = 1;
	}
}

void print_main_list(t_parse_lst *lst)
{
	int i = 0;
	int j = 0;
	while (lst)
	{
		while (lst->args)
		{
			printf("%s\n", lst->args->arg);
			lst->args = lst->args->next;
			j++;
		}
		lst = lst->next;
		i++;
		j = 0;
	}
}