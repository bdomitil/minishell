/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:59:00 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 14:28:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str && !ft_strncmp("-n", str, 2))
	{
		i += 1;
		while (str[i++] == 'n')
			if (str[i] == '\0')
				return (1);
	}
	return (0);
}

void	ft_echo(t_parse_lst *lst)
{
	bool	n_flag;
	t_args	*tmp_arg;

	n_flag = false;
	tmp_arg = lst->args;
	while (tmp_arg && check_flag(tmp_arg->arg))
	{
		tmp_arg = tmp_arg->next;
		n_flag = true;
	}
	while (tmp_arg)
	{
		write(1, tmp_arg->arg, ft_strlen(tmp_arg->arg));
		if (tmp_arg->next)
			write(1, " ", 1);
		tmp_arg = tmp_arg->next;
	}
	if (!n_flag)
		write(1, "\n", 1);
	write(1, (void *)EOF, 4);
	g_mshl.g_exit_status = 0;
}
