#include "headers/parse.h"

int main(void)
{
	char *str= ft_strdup ("echo \"some text is here\" > file1 > file2 | cat file1 < file3");
	// char *str = "echo text";
	t_parse_lst *lst;
	printf("str = %s\n", str);

	if (parser(&str, &lst) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
}