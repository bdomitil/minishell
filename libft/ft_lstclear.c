/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:43:44 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 19:53:01 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst[0] == NULL)
		return ;
	else
	{
		temp = lst[0];
		while (temp)
		{
			lst[0] = lst[0]->next;
			del(temp);
			temp = lst[0];
		}
	}
}
