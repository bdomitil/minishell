/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 00:48:30 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 17:37:09 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

int	parse_str(char **str)
{
	if (*str && not_ending_string(str) == false)
	{
		printf("syntax error: unexpected end of file\n");
		return (-1);
	}
	*str = relese_quoutes(0, *str);
	return (1);
}

int parser(char **str, t_parse_lst **pars_lst)
{
	t_parse_lst *pars_tmp;
	t_args		*args_tmp;

	if (!(*str) || (**str) == '\0' || ft_isempty_str(*str))
		return (1);
	*pars_lst = init_pars_lst();
	if (!(*pars_lst) || !not_ending_string(str) || !fill_lst(*str, *pars_lst))
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	pars_tmp = *pars_lst;
	while (pars_tmp)
	{
		args_tmp = pars_tmp->args;		
		if ((!pars_tmp->command || parse_str(&pars_tmp->command) == -1))  //&& 
			// !join_path(pars_tmp->command))
			return (-1);		
		while (args_tmp != NULL)
		{
			if (args_tmp->arg && parse_str(&args_tmp->arg) == -1)
				return (-1);
			args_tmp = args_tmp->next;
		}
		pars_tmp = pars_tmp->next;
	}

	return (1);
}