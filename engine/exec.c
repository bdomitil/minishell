#include "../headers/minishell.h"

void	exexc(t_parse_lst **lst, char **env)
{
	int		pid;
	char	**cmd;
	t_args	*tmp_args = (*lst)->args;
	int c = 0;
	
	while ((*lst)->args) // посчитать арги 
	{
		(*lst)->args = 
	}
	cmd = (char **)malloc(sizeof(char *) * c); // извлечь аргументы в cmd
	pid = fork();
	if (pid == 0)
	{
		
		rd(*lst);
		execve((*lst)->command, cmd, env);
	}
}