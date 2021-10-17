#include "../headers/minishell.h"

void	change_pwd(t_parse_lst *lst)
{
	t_env	*tmp;
	char	*pwd;
	char 	*cwd;

	tmp = lst->env_lst;
	pwd = getcwd(NULL, 0);
	cwd = ft_strjoin(cwd, pwd);
	write (2, "AAAH\n", 5);
	printf("cwd %s\n", cwd);//(char *)malloc(sizeof (char) * ft_strlen(pwd));
	pwd = find_env_key(lst->env_lst, "PWD");
	if (!ft_strncmp(cwd, pwd, ft_strlen(cwd)) || lst->previous || lst->next)
	{
		printf("1\n");
		return ;
	}
	while (lst->env_lst)
	{
		if (!ft_strncmp("OLDPWD\0", lst->env_lst->key, 7))
		{
//			free (lst->env_lst->value);
			lst->env_lst->value = pwd;
			printf ("old pwd\t%s\n", lst->env_lst->value);
			break;
		}
		lst->env_lst = lst->env_lst->next;
	}
	lst->env_lst = tmp;
	while (lst->env_lst)
	{
		if (!ft_strncmp("PWD\0", lst->env_lst->key, 4))
		{
//			free (lst->env_lst->value);
			lst->env_lst->value = cwd;
			printf ("pwd\t%s\n", lst->env_lst->value);
			break;
		}
		lst->env_lst = lst->env_lst->next;
	}
}

void ft_cd(t_parse_lst *lst) //  errhandle ENOENT
{
	char	*dir;
	char	*env_var;
	char 	*pwd;

	env_var = NULL;
	dir = NULL;
	if (lst->args->next)
		return; // вывести ошибку cd: string not in pwd: ..
		if (!ft_strncmp("~", lst->args->arg, 1))
		{
			env_var = find_env_key(lst->env_lst, "HOME");
			if (env_var)
				dir = ft_strjoin(ft_strjoin(dir, env_var), \
				++(lst->args->arg));
		}
			else if (!ft_strncmp("-", lst->args->arg, 1))
			{
				printf("mi v minuse pacany\n");
				env_var = find_env_key(lst->env_lst, "OLDPWD");
				if (env_var)
					dir = ft_strjoin(dir, env_var);

			}
			else
				dir = ft_strdup(lst->args->arg);
			if (dir)
			{
				if (chdir(dir) == -1)
					printf("error\n"); // errhandle ENOENT
				free(dir);
				free(env_var);
			}
			char *old_pwd;
			old_pwd = NULL;
			pwd = NULL;
			env_var = find_env_key (lst->env_lst, "PWD");
			pwd = ft_strdup(getcwd (NULL, 0));
			if (env_var && pwd)
				if (ft_strcmp(pwd, env_var))
					change_value(lst->env_lst, pwd, "PWD");
			old_pwd = find_env_key(lst->env_lst, "OLDPWD");
			if (!old_pwd)
				add_env_back(&(lst->env_lst), ft_strdup("OLDPWD"), env_var, \
							ft_strjoin(ft_strjoin("OLDPWD", "="), env_var));
			else
				change_value(lst->env_lst, env_var, "OLDPWD");
}