/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:54:22 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:46:03 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	cd_change_env(t_parse_lst *lst, char *pwd)
{
	char	*env_pwd_value;
	char	*env_oldpwd_value;
	char	*tmp;

	env_oldpwd_value = find_env_key(lst->env_lst, "OLDPWD");
	env_pwd_value = find_env_key (lst->env_lst, "PWD");
	if (env_pwd_value)
	{
		if (ft_strcmp(pwd, env_pwd_value))
			change_value(lst->env_lst, pwd, "PWD", false);
	}
	if (!env_oldpwd_value)
	{
		tmp = ft_strjoin("OLDPWD", "=");
		add_env_back(&(lst->env_lst), ft_strdup("OLDPWD"), env_pwd_value, \
			ft_strjoin(tmp, env_pwd_value));
		free (tmp);
	}
	else
		change_value(lst->env_lst, env_pwd_value, "OLDPWD", false);
}

char	*cd_no_args(t_parse_lst *lst)
{
	char	*env_home_value;

	env_home_value = find_env_key(lst->env_lst, "HOME");
	if (!env_home_value)
	{
		error_sh_cmd_msg(1, "cd", NULL, "HOME not set");
		return (NULL);
	}
	return (env_home_value);
}
