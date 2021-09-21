/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:59:54 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 17:28:55 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int q, size_t size)
{
	size_t	i;
	int		*mem;

	i = 0;
	mem = s;
	while (i < size)
	{
		mem[i] = q;
		i++;
	}
	return (s);
}
