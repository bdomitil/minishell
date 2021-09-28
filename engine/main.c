#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
 	char *str= ft_strdup ("<file  cat -e");

    t_parse_lst *lst = NULL;
    if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
    else
		print_pars_lst(&lst);
    // char *bf  = "cdpwdechounsetexportexit";
	io_pipes(&lst);
	
	return 0;
}
