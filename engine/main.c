#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
 	char *str= ft_strdup ("ls -la");

    t_parse_lst *lst = NULL;
    if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
    // else
		// print_pars_lst(&lst);
    // char *bf  = "cdpwdechounsetexportexit";

	// io_pipes(&lst);
	
	
	
	// while (lst)
	// {
		exex(&lst);
		// lst = lst->next;
	// }
	return 0;
}
