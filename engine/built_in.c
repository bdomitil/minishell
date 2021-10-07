#include "../headers/minishell.h"

static void ft_echo(t_parse_lst *lst)
{
	int i; // исправить позже

	i = 0;
	if (!ft_strncmp("-n\0", lst->args->head->arg, 3))
		i = 1;
	if (i && lst->args->next)
		lst->args = lst->args->next;
	while (lst->args)
	{
		write(1, lst->args->arg, ft_strlen(lst->args->arg));
		lst->args = lst->args->next;
	}
	if (i)
		write(1, "\n", 1);
	write(1, (void *)EOF, 4); // может ломать
}

static char *get_HOME(t_parse_lst *lst)
{
	while (lst->env_lst)
	{
		if (!ft_strncmp("HOME\0", lst->env_lst->key, 5))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}

static char *get_OLDPWD(t_parse_lst *lst)
{
	while (lst->env_lst)
	{
		if (!ft_strncmp("OLDPWD\0", lst->env_lst->key, 7))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}

static char *get_PWD(t_parse_lst *lst)
{
	while (lst->env_lst)
	{
		if (!ft_strncmp("PWD\0", lst->env_lst->key, 4))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}

static void ft_pwd(t_parse_lst *lst)
{
	write (1, get_PWD(lst), ft_strlen(get_PWD(lst))); // 0?
	write(1, "\n", 1);
	write(1, (void *)EOF, 4);
}

static void	change_PWD(t_parse_lst *lst)
{
	t_env	*tmp;
	char	*pwd;
	char 	*cwd;

	tmp = lst->env_lst;
	pwd = get_PWD(lst);
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(cwd, pwd, ft_strlen(cwd)))
		return ;
	while (lst->env_lst)
	{
		if (!ft_strncmp("OLDPWD\0", lst->env_lst->key, 7))
		{
			free (lst->env_lst->value);
			lst->env_lst->value = pwd;
		}
		lst->env_lst = lst->env_lst->next;
	}
	lst->env_lst = tmp;
	while (lst->env_lst)
	{
		if (!ft_strncmp("PWD\0", lst->env_lst->key, 4))
		{
			free (lst->env_lst->value);
			lst->env_lst->value = cwd;
		}
		lst->env_lst = lst->env_lst->next;
	}
}

static void ft_cd(t_parse_lst *lst) //  errhandle ENOENT
{
	char	*dir;

	dir = NULL;
	if (lst->args->next)
		return; // вывести ошибку cd: string not in pwd: ../
	if (!ft_strncmp("~", lst->args->arg, 1))
		dir = ft_strjoin(ft_strjoin(dir, get_HOME(lst)), ++(lst->args->arg));
	else if (!ft_strncmp("-", lst->args->arg, 1))
		dir = get_OLDPWD(lst);
	else
		dir = lst->args->arg;
	chdir (dir); // errhandle ENOENT
//	if (ft_strncmp(getcwd (NULL, 0), get_PWD(lst), ft_strlen(getcwd (NULL, 0))))
		change_PWD(lst);
//	{
//		free (get_OLDPWD(lst));
//		get_OLDPWD(lst) = NULL; // shity
//		get_OLDPWD(lst) = get_PWD(lst);
//		free (get_PWD(lst));
//		dir = getcwd (NULL, 0);
//		get_PWD(lst) = dir;
//	}

//	printf("pwd %s\n", getcwd (NULL, 0));
	return;
}

void exe_built_in(t_parse_lst *lst)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		redir(lst);
		close_pipes(lst);
		if (lst->built_in == e_echo)
			ft_echo(lst);
		else if (lst->built_in == e_pwd)
			ft_pwd(lst);
		else if (lst->built_in == e_cd)
			ft_cd(lst);

		exit (0);
	}
}
