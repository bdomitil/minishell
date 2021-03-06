/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:00:49 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

void	ft_env(t_env *env_lst)
{
	while (env_lst)
	{
		if (env_lst->visible)
		{
			write(1, env_lst->key, ft_strlen(env_lst->key));
			write(1, "=", 1);
			write(1, env_lst->value, ft_strlen(env_lst->value));
			write(1, "\n", 1);
		}
		env_lst = env_lst->next;
	}
	write(1, (void *)EOF, 4);
}
