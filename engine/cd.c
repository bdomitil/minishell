#include "../headers/minishell.h"

void ft_cd(t_parse_lst *lst) //  errhandle ENOENT
{
	char	*dir;
	char	*env_var;
	char 	*pwd;

	env_var = NULL;
	dir = NULL;
	if (lst->args->next)
		return; // вывести ошибку cd: string not in pwd: ..
		if (!lst->args) // !ft_strncmp("~", lst->args->arg, 1)
	{
		env_var = find_env_key(lst->env_lst, "HOME");
		if (env_var)
			dir = ft_strjoin(ft_strjoin(dir, env_var), \
			++(lst->args->arg));
		else
		{
			error_sh_cmd_msg(1, "cd", NULL, "HOME not set");
			return;
		}
	}
	else if (!ft_strncmp("-", lst->args->arg, 1))
	{
		env_var = find_env_key(lst->env_lst, "OLDPWD");
		if (env_var)
			dir = ft_strjoin(dir, env_var);
		else
		{
			error_sh_cmd_msg(1, "cd", NULL,"OLDPWD not set");
			return;
		}
	}
	else
		dir = ft_strdup(lst->args->arg);
	if (chdir(dir) == -1)
	{
		error_sh_cmd_msg(1, "cd", NULL, strerror(errno));
		free (dir);
		return;
	}
	free(dir);
	free(env_var);

	char *old_pwd;
	old_pwd = NULL;
	pwd = NULL;
	env_var = find_env_key (lst->env_lst, "PWD");
	pwd = ft_strdup(getcwd (NULL, 0));
	if (!pwd)
	{
		error_sh_cmd_msg(1, "cd", NULL, strerror(errno));
		free (env_var);
		return;
	}
	if (env_var)
		if (ft_strcmp(pwd, env_var))
			change_value(lst->env_lst, pwd, "PWD");
	old_pwd = find_env_key(lst->env_lst, "OLDPWD");
	if (!old_pwd)
		add_env_back(&(lst->env_lst), ft_strdup("OLDPWD"), env_var, \
					ft_strjoin(ft_strjoin("OLDPWD", "="), env_var));
	else
		change_value(lst->env_lst, env_var, "OLDPWD");
	printf("here\n");
}