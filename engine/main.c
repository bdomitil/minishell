#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	char *str;
	t_parse_lst *lst = NULL;
    t_parse_lst *head = NULL;

	(void)argc, (void)argv;
	while ((str = readline("$mini$hee$h$")))
	{

		add_history(str);
		errno = 0;
		if (parser(&str, &lst, env) == -1)
		{
			printf("\n\n______ERROR______\n\n");
			continue;
		}
//		else
		print_pars_lst(&lst);  //delete it later
		head = lst->head;
		io_pipes(lst);

		while (lst)
		{
			exex(&lst);
			lst = lst->next;
		}
		lst = head;
		close_pipes(lst);
		clean_main_list(lst);
		lst = NULL;
//		free(lst);
	}
	return 0;
}
