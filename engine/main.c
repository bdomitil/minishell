#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
 	char *str= ft_strdup ("<f1 cat | cat >f2 ");

    t_parse_lst *lst = NULL;
    t_parse_lst *head = NULL;
    if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
    // char *bif  = "cdpwdechounsetexportexit";

	io_pipes(lst);
	print_pars_lst(&lst);
	head = lst;
	while (lst)
	{
		exex(&lst);
		lst = lst->next;
	}
//	printf("actual-lst cmd %s\n",lst->command);
	lst = head;
	close_pipes(lst);
	if (lst->next && (lst)->fd_in != 1)
		close((lst)->fd_in);
	return 0;
}
