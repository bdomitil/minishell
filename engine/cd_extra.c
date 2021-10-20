#include "../headers/minishell.h"

void cd_change_env(t_parse_lst *lst, char *pwd)
{
	char	*env_pwd_value;
	char 	*env_oldpwd_value;
	char	*tmp;

	env_oldpwd_value = find_env_key(lst->env_lst, "OLDPWD");;
	env_pwd_value = find_env_key (lst->env_lst, "PWD");
	if (env_pwd_value)
	{
		if (ft_strcmp(pwd, env_pwd_value))
			change_value(lst->env_lst, pwd, "PWD");
	}
	if (!env_oldpwd_value)
	{
		tmp = ft_strjoin("OLDPWD", "=");
		add_env_back(&(lst->env_lst), ft_strdup("OLDPWD"), env_pwd_value, \
			ft_strjoin(tmp, env_pwd_value));
		free (tmp);
	}
	else
		change_value(lst->env_lst, env_pwd_value, "OLDPWD");
}