/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 02:18:23 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/19 00:49:43 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		pos;
	char	*to_ret;

	i = 0;
	pos = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	to_ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!to_ret)
		return (NULL);
	else
	{
		while (s1 && s1[i] != '\0')
			to_ret[pos++] = s1[i++];
		i = 0;
		while (s2 && s2[i] != '\0')
		{
			to_ret[pos] = s2[i++];
			pos++;
		}
		to_ret[pos] = '\0';
	}
	return (to_ret);
}
