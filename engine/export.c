#include "../headers/minishell.h"

//t_env	*sort_env_by_ascii(t_env *env_lst) // rename
//{
//	t_env	*tmp;
//	char	a;
//
//	a = 65; // 65 - 90 , 97 - 199
//	tmp = env_lst;
//	while (env_lst)
//	{
//		while (env_lst)
//		{
//
//		}
//		if ()
//		env_lst = env_lst->next;
//		a++;
//	}
//	a = 0;// 0 - 64, 91 - 96
//	while (env_lst)
//}

static void	print_export(t_env *env_lst)
{
	char	a[1];

	a[0] = 34;
	while (env_lst)
	{
		write(1, "declare -x ", 11);
		write(1, env_lst->key, ft_strlen(env_lst->key));
		write(1, "=", 2);
		write(1, a, 2);
		write(1, env_lst->value, ft_strlen(env_lst->value));
		write(1, a, 2);
		write(1, "\n", 1);
		env_lst = env_lst->next;
	}
	write(1, (void *)EOF, 4); // может ломать
}


void	ft_export(t_parse_lst *lst)
{
	char	*tmp;
	char 	*key;
	char 	*value;
	char 	*pos;
	t_env	*env_lst;


	if (!lst->args)
		print_export(lst->env_lst);
	while (lst->args)
	{
		value = NULL; // ?
		tmp = ft_strdup(lst->args->arg);
		pos = ft_strchr(tmp, '=');
		if (pos)
		{
			value = ft_strdup(pos + 1);
			*pos = '\0';
		}
		key = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strdup(lst->args->arg);
		add_env_back(&env_lst, key, value, tmp);
		lst->args = lst->args->next;
	}
}
