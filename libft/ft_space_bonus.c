/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:26:31 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/01 11:29:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_space(int q)
{
	char	*space;
	int		i;

	i = 0;
	space = "\t\v\f\r\n ";
	while (space[i] != '\0')
		if (q == space[i++])
			return (1);
	return (0);
}
