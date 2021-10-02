#include "../headers/minishell.h"

static char **envp(t_env *env)
{
	char	**envarray;
	int		size = 1;
	t_env	*tmp_env;

	tmp_env = env;
	while (env)
	{
		size++;		
		env = env->next;
	}
	envarray = (char **)malloc (sizeof(char *) * size);
	if (!envarray)
		return(NULL);
	size = 0;
	while (tmp_env)
	{
		envarray[size++] = tmp_env->env_type;
		tmp_env = tmp_env->next;
	}
	envarray[size] = NULL;
	return (envarray);
}

void	exex(t_parse_lst **lst)
{
	pid_t		pid;
	char	**cmd = NULL;

	char	**env = envp((*lst)->env_lst);
	if ((*lst)->args)	
		cmd = (char **)malloc(sizeof(char *) * ((*lst)->args->tail->id + 3)); // извлечь аргументы в cmd
	else
		cmd = (char **)malloc(sizeof(char *) * 2); // извлечь аргументы в cmd
	int i = 1;
	cmd[0] = (*lst)->command;
	join_path(&((*lst)->command), (*lst)->env_lst);
	
	while ( (*lst)->args && i < (*lst)->args->tail->id + 2)
	{
		cmd[i] = (*lst)->args->arg;
		(*lst)->args = (*lst)->args->next;
		i++;
	}

	cmd[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		redir(lst);
		close_pipes(*lst);
		execve((*lst)->command, cmd, env);
	}
	// else
		// wait(NULL);
}