/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:11:15 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 19:54:05 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*to_ret;

	if (!lst || !f || !del)
		return (NULL);
	to_ret = NULL;
	while (lst)
	{
		new = ft_lstnew(lst->content);
		if (!new)
		{
			del(to_ret);
			return (NULL);
		}
		new->content = f(new->content);
		ft_lstadd_back(&to_ret, new);
		lst = lst->next;
	}
	ft_lstadd_back(&to_ret, NULL);
	return (to_ret);
}
