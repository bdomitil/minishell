#include "headers/parse.h"

int main(int argc, char **argv, char **env)
{
 	// char *str= ft_strdup ("echo aza \"hello world\"  > \'file1\' >   \"file2\"   >file3   \">not_file\"  \"		| \"  \"  ab \"grep $var << \"stop1\"  <<stop2<file	\
		| 	grep greping_str > file_file " );
	// char *str = ft_strdup(" \"e\"\"c\"\"h\"\"o\" ");
	// t_parse_lst *lst = NULL;
	// printf("str = %s\n", str);
	// errno = 0;
	// if (parser(&str, &lst, env) == -1)
	// 	printf("\n\n______ERROR______\n\n");
	// else
	// 	print_pars_lst(&lst);  //delete it later
	char *str;
	while ((str = readline("mybash >>  ")))
	{
		add_history(str);
		t_parse_lst *lst = NULL;
		printf("\n_______________\n");
		// printf("str = %s\n", str);
		errno = 0;
		if (parser(&str, &lst, env) == -1)
			printf("\n\n______ERROR______\n\n");
		else
			print_pars_lst(&lst);  //delete it later
	}
	// while (1);
}