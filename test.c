#include "headers/parse.h"

int main(int argc, char **argv, char **env)
{
	parse_env(env);
	exit(0);
 	char *str= ft_strdup ("echo aza \"hello world\"  > \'file1\' >   \"file2\"   >file3   \">not_file\"  \" | \"  \"  ab \"grep $var << \"stop1\"    <<stop2<file " );
	// char *str = ft_strdup(" echo \"hello world\\\"\"\"\'$var\'\"");
	t_parse_lst *lst;
	printf("str = %s\n", str);
	errno = 0;
	if (parser(&str, &lst, env) == -1)
		printf("\n\n______ERROR______\n\n");
	else
		print_pars_lst(&lst);  //delete it later
	// while (1);
}