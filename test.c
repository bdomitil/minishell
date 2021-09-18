#include "headers/parse.h"

int main(void)
{
	char *str= ft_strdup ("echo some text gg  here >> file1 >> file2 < file3 << stop << stop1 << stop2");
	// char *str = ft_strdup("echo  \\z");
	t_parse_lst *lst;
	printf("str = %s\n", str);
	errno = 0;
	if (parser(&str, &lst) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
}