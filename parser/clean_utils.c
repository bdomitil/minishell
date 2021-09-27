/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 01:13:51 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 16:05:03 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

void	*free_string_mass(char **mass, int size, int use_size)
{
	int	i;

	i = -1;
	if (use_size)
		while (i < size)
			free(mass[i]);
	else
		while (mass[++i])
			free(mass[i]);
	return (NULL);
}

void	free_dev_lst(t_deviders **devider)
{
	t_deviders	*tmp;

	while (*devider)
	{
		tmp = *devider;
		(*devider) = (*devider)->next;
		free(tmp);
	}
}
