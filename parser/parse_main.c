/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 00:48:30 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/21 18:03:37 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/parse.h"

int	get_lst_parsed(t_parse_lst *pars_lst)
{
	t_args	*args_tmp;

	while (pars_lst)
	{
		args_tmp = pars_lst->args;
		if ((!pars_lst->command && !pars_lst->stop_list) ||\
						parse_str(&pars_lst->command, pars_lst->env_lst) == -1)
			return (-1);
		while (args_tmp != NULL)
		{
			if (args_tmp->arg && \
						parse_str(&args_tmp->arg, pars_lst->env_lst) == -1)
				return (-1);
			args_tmp = args_tmp->next;
		}
		pars_lst = pars_lst->next;
	}
	return (1);
}

int	parse_str(char **str, t_env *env_lst)
{
	if (*str && !not_ending_string(str))
		return (-1);
	else if (!(*str))
		return (0);
	*str = relese_quoutes(0, *str, env_lst);
	return (1);
}

int	parser(char **str, t_parse_lst **pars_lst, t_env *env_lst)
{
	if (!(*str) || (**str) == '\0' || ft_isempty_str(*str))
	{
		return (0);
	}
	*pars_lst = init_pars_lst();
	if (!(*pars_lst) || \
		!not_ending_string(str) || \
		!fill_lst(*str, *pars_lst, env_lst))
		return (-1);
	return (get_lst_parsed(*pars_lst));
}
