/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:22:42 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:07:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	print_export(t_env *env_lst)
{
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
	write(1, (void *)EOF, 4);
}

bool	change_value(t_env *env_lst, char *value, char *key, bool plus)
{
	char	*tmp;

	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key) && value)
		{
			env_lst->visible = true;
			if (plus)
			{
				tmp = env_lst->value;
				env_lst->value = ft_strjoin(env_lst->value, value);
				free (tmp);
				free(value);
			} else
			{
				if (env_lst->value)
					free(env_lst->value);
				env_lst->value = value;
			}
			return (true);
		} else if (!ft_strcmp(key, env_lst->key))
			return (true);
		env_lst = env_lst->next;
	}
	return (false);
}

static void	push_to_env(char *tmp, char *key, char *value, t_parse_lst *lst)
{
	bool	plus;
	char	*pos;

	plus = false;
	pos = ft_strchr(tmp, '=');
	if (pos && *(--pos) == '+')
	{
		pos = ft_strchr(key, '+');
		*pos = '\0';
		plus = true;
	}
	if (!change_value(lst->env_lst, value, key, plus))
	{
		free (tmp);
		tmp = ft_strdup(lst->args->arg);
		add_env_back(&(lst->env_lst), key, value, tmp);
	}
	else
		free(key);
}

static void	get_value_and_key(char **value, char *tmp, char **key)
{
	char	*pos;

	pos = NULL;
	pos = ft_strchr(tmp, '=');
	if (pos)
	{
		*value = ft_strdup(pos + 1);
		*pos = '\0';
	}
	*key = ft_strdup(tmp);
	if (pos)
		*pos = '=';
}

void	ft_export(t_parse_lst *lst)
{
	char	*tmp;
	char	*key;
	char	*value;
	t_args	*tmp_arg;

	if (!lst->args)
		print_export(lst->env_lst);
	tmp_arg = lst->args;
	while (tmp_arg && tmp_arg->arg)
	{
		value = NULL;
		tmp = ft_strdup(tmp_arg->arg);
		if (!valid_export_arg(tmp))
			return ;
		get_value_and_key(&value, tmp, &key);
		push_to_env(tmp, key, value, lst);
		tmp_arg = tmp_arg->next;
	}
	g_mshl.g_exit_status = 0;
}
