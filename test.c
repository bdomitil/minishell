#include "headers/parse.h"

int main(void)
{
 	char *str= ft_strdup ("echo aza \"hello world\" > \'file1\' > \"file2\">file3 \">not_file\" | grep $var << \"stop1\" <<stop2");
	t_parse_lst *lst;
	printf("str = %s\n", str);
	errno = 0;
	if (parser(&str, &lst) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
	while (1);
}