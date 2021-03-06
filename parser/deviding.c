/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 22:13:30 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 20:10:37 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static int	parse_built_in(char *command)
{
	if (!ft_strcmp("echo", command))
		return (e_echo);
	else if (!ft_strcmp("cd", command))
		return (e_cd);
	else if (!ft_strcmp("pwd", command))
		return (e_pwd);
	else if (!ft_strcmp("export", command))
		return (e_export);
	else if (!ft_strcmp("unset", command))
		return (e_unset);
	else if (!ft_strcmp("env", command))
		return (e_env);
	else if (!ft_strcmp("exit", command))
		return (e_exit);
	else
		return (0);
}

void	commands_args_fill(t_parse_lst *current_pars, char **command_params, \
																t_env *env_lst)
{
	t_args	*new_args;

	if (!command_params || !(*command_params))
		return ;
	current_pars->command = *command_params;
	current_pars->built_in = parse_built_in(current_pars->command);
	current_pars->env_lst = env_lst;
	command_params++;
	while (*command_params)
	{
		new_args = init_arg_lst(*command_params);
		ft_args_lst_add_back(current_pars, new_args);
		command_params++;
	}
}

char	*cut_str_by_devider(char *str, t_deviders *dev_lst, \
							char ***command_params, t_parse_lst *pars_lst)
{
	t_parse_lst	*new_pars;
	char		*tmp;
	char		*to_ret;

	tmp = str;
	str[dev_lst->pos_in_str] = '\0';
	*command_params = split_out_quotes(str, ' ');
	new_pars = init_pars_lst();
	ft_shell_lst_add_back(pars_lst, new_pars);
	to_ret = ft_strdup(&str[dev_lst->pos_in_str + 1]);
	free(tmp);
	return (to_ret);
}

int	fill_lst(char *str, t_parse_lst *pars_lst, t_env *env_lst)
{
	t_deviders	*dev_lst;
	t_deviders	*to_free;
	char		**command_params;

	dev_lst = get_deviders_list(str);
	while (dev_lst)
	{
		if (get_redir_fd(pars_lst, &dev_lst, &str) == -1)
		{
			g_mshl.g_exit_status = errno;
			return (0);
		}
		else if (!dev_lst)
			break ;
		str = cut_str_by_devider(str, dev_lst, &command_params, pars_lst);
		pars_lst->pipe = dev_lst->type == pipe_is_next;
		commands_args_fill(pars_lst, command_params, env_lst);
		pars_lst = pars_lst->next;
		to_free = dev_lst;
		free(to_free);
		dev_lst = dev_lst->next, free(command_params);
	}
	command_params = split_out_quotes(str, ' ');
	commands_args_fill(pars_lst, command_params, env_lst);
	free(command_params), free(str);
	return (1);
}
