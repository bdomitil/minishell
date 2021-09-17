#include "headers/parse.h"

int main(int argc, char **argv)
{
	// char *str = ft_strdup("echo hello \\\"> file world < file2 > file3 and \"another world\"  | grep qwe");
	char *str= ft_strdup ("echo \" some_text \" > file1");
	t_parse_lst *lst;
	printf("\n%s\n", str);

	if (parser(&str, &lst) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
	// while (1);
}