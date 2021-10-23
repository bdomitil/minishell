/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:45:28 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 19:53:50 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*temp;
	t_list	*buff;

	if (lst == NULL)
		return ;
	temp = lst;
	while (temp != NULL)
	{
		buff = temp->next;
		f(temp->content);
		temp = buff;
	}
	return ;
}
