#include "../headers/minishell.h"

char	**envprint(t_env *env)
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
	pid_t	pid;
	char	**cmd = NULL;

	char	**env = envprint((*lst)->env_lst);
	if ((*lst)->args)
		cmd = (char **)malloc(sizeof(char *) * ((*lst)->args->tail->id + 3));
	else
		cmd = (char **)malloc(sizeof(char *) * 2);
	int i = 1;
	cmd[0] = ft_strdup((*lst)->command);

	while ((*lst)->args && i < (*lst)->args->tail->id + 2)
	{
		cmd[i] = (*lst)->args->arg;
		(*lst)->args = (*lst)->args->next;
		i++;
	}
	cmd[i] = NULL;
	join_path(&((*lst)->command), (*lst)->env_lst);
	if ((*lst)->fd_in == -2)
	{
		int pfd[2];
		if (!here_doc((*lst), pfd))
			return ;
	}
	pid = fork();
	if (pid == 0) // child
	{
		if (!redir(*lst))
			exit(-1);
		if (!close_fds(*lst))
			exit(-1);
		if (execve((*lst)->command, cmd, env) == -1)
			exit(-1);
	}
	else
	{
		(*lst)->pid = pid;
	}
}