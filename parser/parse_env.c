/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 02:55:56 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 18:48:14 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

void	add_env_back(t_env **env_lst, char *key, char *value, char *env_type)
{
	t_env	*tmp;

	if (!(*env_lst))
	{
		*env_lst = malloc(sizeof(t_env));
		(*env_lst)->key = key;
		(*env_lst)->visible = (bool)value;
		(*env_lst)->env_type = env_type;
		(*env_lst)->value = value;
		(*env_lst)->next = NULL;
		return ;
	}
	else
		tmp = *env_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->value = value;
	tmp->next->visible = (bool)value;
	tmp->next->env_type = env_type;
	tmp->next->key = key;
	tmp->next->next = NULL;
}

void	del_env_lst_by_key(t_env *env_lst, char *key)
{
	t_env	*tmp_lst;

	tmp_lst = NULL;
	while (env_lst)
	{
		if (!strcmp(key, env_lst->key))
		{
			if (tmp_lst)
				tmp_lst->next = env_lst->next;
			free(env_lst->key);
			if (env_lst->value)
				free(env_lst->value);
			free(env_lst->env_type);
			free(env_lst);
			env_lst = NULL;
			return ;
		}
		tmp_lst = env_lst;
		env_lst = env_lst->next;
	}
}

char	*find_env_key(t_env *env_lst, char *key)
{
	if (!env_lst)
		return (NULL);
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return (ft_strdup(env_lst->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_env	*parse_env(char **env)
{
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*env_lst;

	env_lst = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "OLDPWD", 6) || !ft_strlen(*env))
		{
			env++;
			continue ;
		}
		tmp = ft_strdup(*env);
		if (ft_strchr(tmp, '='))
			value = ft_strdup(ft_strchr(tmp, '=') + 1);
		else
			value = NULL;
		key = ft_substr(tmp, 0, ft_strchr(tmp, '=') - tmp);
		free(tmp);
		env++;
		add_env_back(&env_lst, key, value, ft_strdup(*env));
	}
	return (env_lst);
}
