/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 03:21:41 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 20:05:39 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *where, const char *what, size_t size)
{
	size_t	i;
	char	word[100];
	char	temp[100];

	ft_strlcpy(word, (char *)where, size + 1);
	ft_strlen(where);
	i = 0;
	while (i <= ft_strlen(word))
	{
		ft_strlcpy(temp, &word[i], ft_strlen(what) + 1);
		if (ft_strcmp(temp, what) == 0)
			return ((char *)&where[i]);
		i++;
	}
	return (NULL);
}
