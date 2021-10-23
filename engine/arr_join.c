/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:47:42 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:33:58 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

static int	arrsize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**arrjoin(char **arr, char *str)
{
	char	**newarr;
	int		size;
	int		i;

	if (!arr)
	{
		newarr = (char **)malloc(sizeof(char *) * 2);
		newarr[0] = str;
		newarr[1] = NULL;
		return (newarr);
	}
	size = arrsize(arr);
	newarr = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (arr[i])
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = str;
	i++;
	newarr[i] = NULL;
	return (newarr);
}
