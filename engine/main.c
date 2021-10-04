#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
 	char *str= ft_strdup ("< test1.txt cat | cat > file2.txt | pwd | cat > file3.txt");
	//  char *str = ft_strdup("echo some ards | << stop1 << _stop2 << stop_3");
	(void)argc;
	(void)argv;
    t_parse_lst *lst = NULL;
    t_parse_lst *head = NULL;
    if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
    else
        print_pars_lst(&lst);
    // char *bif  = "cdpwdechounsetexportexit";

	head = lst->head;
	io_pipes(lst);
	lst = head;
	while (lst)
	{
		exex(&lst);
		lst = lst->next;
	}
//	printf("actual-lst cmd %s\n",lst->command);
	lst = head;
	close_pipes(lst);
	return 0;
}
