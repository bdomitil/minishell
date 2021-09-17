/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 22:13:30 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/17 20:21:34 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

void	commands_args_fill(t_parse_lst *current_pars, char **command_params,\
	t_deviders *dev_lst)
{
	t_args      *new_args;
	if (!command_params)
		return ;
	current_pars->command = *command_params;
	command_params++;
	// else if (prev_type == none || prev_type == pipe_is_next)
	// {
	// 	current_pars->command = *command_params;
	// 	command_params++;
	// }
	// else
	// {
	// 	current_pars->file_fd = get_redir_fd(dev_lst->type, current_pars,\
	// 		current_pars->command);
	// 	command_params++;
	// }
	while (*command_params)
	{
		new_args = init_arg_lst();
		new_args->arg = *command_params;
		ft_args_lst_add_back(current_pars, new_args);
		command_params++;
	}
}

char	*cut_str_by_devider(char *str, t_deviders *dev_lst, char ***command_params,\
	t_parse_lst *pars_lst)
{
	t_parse_lst *new_pars;
	str[dev_lst->pos_in_str] = '\0';
	*command_params = split_out_quotes(str, ' ');
	new_pars = init_pars_lst();
	ft_shell_lst_add_back(pars_lst, new_pars);
	if (dev_lst->type == double_redir_is_next)
		return (&str[dev_lst->pos_in_str + 2]);
	else
		return (&str[dev_lst->pos_in_str + 1]);
}

int fill_lst(char *str, t_parse_lst *pars_lst)
{
	t_deviders  *dev_lst;
	t_deviders  *temp;
	t_parse_lst *current_pars;
	char        **command_params;

	command_params = NULL;
	dev_lst = get_deviders_list(str);
	current_pars = pars_lst;
	while (dev_lst)
	{
		if (get_redir_fd(current_pars, &dev_lst, &str) == -1)
			return(0);
		else if (!dev_lst)
			break ;
		str = cut_str_by_devider(str, dev_lst, &command_params, pars_lst);
		if (dev_lst->type == pipe_is_next)
			current_pars->pipe = true;
		temp = dev_lst;
		commands_args_fill(current_pars, command_params, dev_lst);
		current_pars = current_pars->next;
		free(temp);
		if (dev_lst)
			dev_lst = dev_lst->next;
	}
	command_params = split_out_quotes(str, ' ');
	commands_args_fill(current_pars, command_params, dev_lst);
	return (1);
}