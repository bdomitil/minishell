/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:49:07 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/01 11:29:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const	unsigned	char	*str;
	size_t						i;

	str = (const unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == str[i])
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
