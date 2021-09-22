#include "headers/parse.h"

int main(int argc, char **argv, char **env)
{
 	// char *str= ft_strdup ("echo aza \"hello world\"  > \'file1\' >   \"file2\"   >file3   \">not_file\"  \" | \"  \"  ab \"grep $var << \"stop1\"    <<stop2<file " );
	char *str = ft_strdup(" echo $USER $SHLVL");
	t_parse_lst *lst = NULL;
	printf("str = %s\n", str);
	errno = 0;
	if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
	// while (1)
	// {
	// char *str = NULL;
	// t_parse_lst *lst = NULL;
	// get_next_line(0, &str);
	// printf("\n_______________\n");
	// // printf("str = %s\n", str);
	// errno = 0;
	// if (parser(&str, &lst, env) == -1)
	// 	printf("\n\n______ERROR______\n\n");
	// else
	// 	print_pars_lst(&lst);  //delete it later
	// }
	// while (1);
}