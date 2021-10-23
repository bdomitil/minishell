/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:16:31 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 21:20:44 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

char    *key_value(char *key, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(key, "=");
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, value);
	free(tmp2);
	return (tmp);
}