/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 02:55:56 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/23 22:42:35 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

char	*change_sh_lvl(char *shlvl)
{
	int		lvl;

	lvl = ft_atoi(shlvl);
	lvl++;
	free(shlvl);
	return (ft_itoa(lvl));
}
