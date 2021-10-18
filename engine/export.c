#include "../headers/minishell.h"

static void	print_export(t_env *env_lst)
{
	print_env_lst(env_lst);
	while (env_lst)
	{
		write(1, "declare -x ", 11);
		write(1, env_lst->key, ft_strlen(env_lst->key));
		if (env_lst->visible)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, env_lst->value, ft_strlen(env_lst->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env_lst = env_lst->next;
	}
	write(1, (void *)EOF, 4); // может ломать
}

//	t_env	*
//	char *fek;
//	fek = find_env_key(lst->env_lst, key);
//	if (fek) // код ошибки
//	{
//		free (tmp);
//		free (value);
//		free (key);
//		return ;
//	}
bool	change_value(t_env *env_lst, char *value, char *key)
{
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
		{
			if (env_lst->value)
				free(env_lst->value);
			env_lst->value = value;
			return (true);
		}
		env_lst = env_lst->next;
	}
	return (false);
}

void	ft_export(t_parse_lst *lst)
{
	char	*tmp;
	char 	*key;
	char 	*value;
	char 	*pos;
	t_args	*tmp_arg;

	if (!lst->args)
	{
		print_export(lst->env_lst);
		return;
	}
	tmp_arg = lst->args;
	while (tmp_arg && tmp_arg->arg)
	{
		value = NULL;
		tmp = ft_strdup(tmp_arg->arg); // free
		pos = ft_strchr(tmp, '=');
		if (pos)
		{
			value = ft_strdup(pos + 1);
			*pos = '\0';
		}
		key = ft_strdup(tmp); // free
		if (! change_value(lst->env_lst, value, key))
		{
			free (tmp);
			tmp = ft_strdup(tmp_arg->arg);
			add_env_back(&(lst->env_lst), key, value, tmp);
		}
		else
			free(key);
		tmp_arg = tmp_arg->next;
	}
}
