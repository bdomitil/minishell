#include "headers/parse.h"

int main(int argc, char **argv)
{
	char *str = ft_strdup("<file  << echo home ls ");
	t_parse_lst *lst;
	printf("\n%s\n", str);

	if (parser(&str, &lst) == -1 || lst == NULL)
		printf("\n\n______ERROR______\n\n");
	print_pars_lst(&lst);  //delete it later


	// while (1);
}