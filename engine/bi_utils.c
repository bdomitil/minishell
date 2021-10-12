#include "../headers/minishell.h"

char *get_HOME(t_parse_lst *lst)
{
	while (lst->env_lst)
	{
		if (!ft_strncmp("HOME\0", lst->env_lst->key, 5))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}

char	*get_PWD(t_parse_lst *lst)
{
	printf("env_lst = %p\n", lst->env_lst);
	while (lst->env_lst)
	{
		if (!ft_strncmp("PWD\0", lst->env_lst->key, 4))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}

char	*get_OLDPWD(t_parse_lst *lst)
{
	while (lst->env_lst)
	{
		if (!ft_strncmp("OLDPWD\0", lst->env_lst->key, 7))
			return (lst->env_lst->value);
		lst->env_lst = lst->env_lst->next;
	}
	return (NULL);// !err handle
}