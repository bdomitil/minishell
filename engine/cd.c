#include "../headers/minishell.h"

void	change_PWD(t_parse_lst *lst)
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

	dir = NULL;
	if (lst->args->next)
		return; // вывести ошибку cd: string not in pwd: ..
		if (!ft_strncmp("~", lst->args->arg, 1))
			dir = ft_strjoin(ft_strjoin(dir, find_env_key(lst->env_lst, "HOME")), ++(lst->args->arg)); // проверить изменяется ли потом
			else if (!ft_strncmp("-", lst->args->arg, 1))
				dir = ft_strjoin(dir, find_env_key(lst->env_lst, "OLDPWD"));
			else if (!ft_strcmp(".\0", lst->args->arg))
			{
				//		printf("sd\n");
				dir = (char *)malloc(sizeof (char *) * 3);
				dir = "./\0";
			}
			else if (!ft_strcmp("..\0", lst->args->arg))
			{
				//		printf("AAAAH\n");
				dir = (char *)malloc(sizeof (char *) * 4);
				//		dir = ft_strcpy(dir, "../\0");
				dir = "../\0";
			}
			else
				dir = lst->args->arg;
			chdir (dir); // errhandle ENOENT
			//	free (dir);
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
			//		return;
}

//void	ft_cd(t_parse_lst *lst) //  err-handle ENOENT
//{
//	char	*dir;
//
//	dir = NULL;
//	if (lst->args->next)
//		return; // выв ести ошибку cd: string not in pwd: ../
//		if (!ft_strncmp("~", lst->args->arg, 1))
//			dir = ft_strjoin(ft_strjoin(dir, get_HOME(lst)), ++(lst->args->arg));
//		else if (!ft_strncmp("-", lst->args->arg, 1))
//			dir = get_OLDPWD(lst);
//		else
//			dir = lst->args->arg;
//		chdir (dir); // errhandle ENOENT
//		change_PWD(lst);
//		return;
//}