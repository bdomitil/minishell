/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviding_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:00:58 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/05 20:25:41 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static t_deviders	*lstnew_devide(int *pos, t_found devider_type)
{
	t_deviders *new_list;

	new_list = malloc(sizeof(t_deviders));
	if (!new_list)
		return (NULL);
	new_list->pos_in_str = *pos;
    new_list->type = devider_type;
	new_list->next = NULL;
	*pos = -1;
	return (new_list);
}

static int	lstadd_back_devide(t_deviders **lst, t_deviders *new, char *str)
{
	t_deviders *temp;

	if (*lst == NULL)
	{
		*lst = new;
		return (1);
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return(1);
}

t_deviders *get_deviders_list(char *str)
{
	int			i;
	int			pos;
	t_deviders	*deviders;
	int			qt_opened;

	i = 0;
	pos = 0;
	qt_opened = -1;
	deviders = NULL;
	while (str[i] != '\0')
	{
		if (qt_opened >= 0 && find_next_quote(str, i, '\"') != qt_opened)
			qt_opened = -1;
		else
			qt_opened = find_next_quote(str, i, '\"');
		if (str[i] == '|' && qt_opened == -1)
			lstadd_back_devide(&deviders, lstnew_devide(&pos, pipe_is_next), str);




			
		else if (str[i] == '<' && str[i + 1] == '<' && qt_opened == -1)
		{
			lstadd_back_devide(&deviders, lstnew_devide(&pos, double_back_redir_is_next), str);
			i += 2;
		}
		else if (str[i] == '<' && qt_opened == -1)
				lstadd_back_devide(&deviders, lstnew_devide(&pos, back_redir_is_next), str);
		else if (str[i] == '>' && str[i + 1] == '>' && qt_opened == -1)
		{
			lstadd_back_devide(&deviders, lstnew_devide(&pos, double_redir_is_next), str);
			i++;
		}
		else if (str[i] == '>' && qt_opened == -1)
			lstadd_back_devide(&deviders, lstnew_devide(&pos, redir_is_next), str);
		pos++;
		i++;
	}
	return (deviders);
}
