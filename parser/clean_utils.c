/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 01:13:51 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/19 01:35:10 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

void	free_dev_lst(t_deviders **devider)
{
	t_deviders *tmp;

	while (*devider)
	{
		tmp = *devider;
		(*devider) = (*devider)->next;
		free(tmp);
	}
}