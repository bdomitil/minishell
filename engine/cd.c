/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:36:39 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 15:38:34 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*tilda(t_parse_lst *lst)
{
	char	*env_home_value;
	char	*ret;

	env_home_value = find_env_key(lst->env_lst, "HOME");
	if (!env_home_value)
	{
		error_sh_cmd_msg(1, "cd", NULL, "HOME not set");
		return (NULL);
	}
	if (lst->args)
	{
		ret = ft_strjoin(env_home_value, ++(lst->args->arg));
		free (env_home_value);
		return (ret);
	}
	else
		return (env_home_value);
}

static char	*minus(t_parse_lst *lst)
{
	char	*env_oldpwd_value;

	env_oldpwd_value = find_env_key(lst->env_lst, "OLDPWD");
	if (env_oldpwd_value)
		return (env_oldpwd_value);
	else
	{
		error_sh_cmd_msg(1, "cd", NULL, "OLDPWD not set");
		return (NULL);
	}
}

static bool	define_dir(char **dir, char *pwd, t_parse_lst *lst)
{
	if (!lst->args)
		*dir = cd_no_args(lst);
	else if (!ft_strncmp("~", lst->args->arg, 1))
		*dir = tilda(lst);
	else if (!ft_strncmp("-", lst->args->arg, 1))
		*dir = minus(lst);
	else if (!ft_strncmp("..", lst->args->arg, 2))
	{
		if (pwd)
		{
			if (ft_strcmp("/", pwd))
				*dir = ft_strdup(lst->args->arg);
			else
				return (false);
		}
		else
			*dir = find_env_key(lst->env_lst, "OLDPWD");
	}
	else
		*dir = ft_strdup(lst->args->arg);
	return (true);
}

static bool	actually_chdir(char *dir, char *pwd)
{
	if (chdir(dir) == -1)
	{
		error_sh_cmd_msg(1, "cd", NULL, strerror(errno));
		free(dir);
		free (pwd);
		return (false);
	}
	free(dir);
	return (true);
}

void	ft_cd(t_parse_lst *lst)
{
	char	*dir;
	char	*pwd;

	dir = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd && ft_strncmp("..", lst->args->arg, 2))
	{
		error_sh_cmd_msg(1, "cd", NULL, strerror(errno));
		return ;
	}
	if (!define_dir(&dir, pwd, lst))
		return ;
	if (dir)
		if (!actually_chdir(dir, pwd))
			return ;
	if (pwd)
		free (pwd);
	pwd = getcwd(NULL, 0);
	cd_change_env(lst, pwd);
}
