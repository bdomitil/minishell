#include "../headers/minishell.h"

char **env(t_parse_lst **lst)
{
	
}

void	exex(t_parse_lst **lst)
{
	int		pid;
	char	**cmd;
	// t_args	*tmp_args = (*lst)->args;
	int c = 0;
	
	while ((*lst)->args->next)
		(*lst)->args = (*lst)->args->next;
	
	cmd = (char **)malloc(sizeof(char *) * ((*lst)->args->id + 1)); // извлечь аргументы в cmd
	int i = (*lst)->args->id;
	
	while (i >= 0)
	{
		cmd[i] = (*lst)->args->arg;
		(*lst)->args = (*lst)->args->previous;
		i--;
	}

	pid = fork();
	if (pid == 0)
	{
		rd(*lst);
		execve((*lst)->command, cmd, env);
	}
}