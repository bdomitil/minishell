/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviding_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:00:58 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/18 16:02:00 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static t_deviders	*lstnew_devide(int *pos, t_found devider_type)
{
	t_deviders	*new_list;

	new_list = malloc(sizeof(t_deviders));
	if (!new_list)
		return (NULL);
	if (devider_type == double_redir_is_next || \
								devider_type == double_back_redir_is_next)
		new_list->pos_in_str = *pos + 1;
	else
		new_list->pos_in_str = *pos;
	new_list->type = devider_type;
	new_list->next = NULL;
	if (devider_type == pipe_is_next)
		*pos = -1;
	return (new_list);
}

static int	lstadd_back_devide(t_deviders **lst, t_deviders *new)
{
	t_deviders	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return (1);
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (1);
}

int	get_devider(char *q, int qt_opened, int *pos, t_deviders **deviders)
{
	if (*q == '|' && qt_opened == -1)
		lstadd_back_devide(deviders, lstnew_devide(pos, pipe_is_next));
	else if (*q == '<' && *(q + 1) == '<' && qt_opened == -1)
	{
		lstadd_back_devide(deviders, \
						lstnew_devide(pos, double_back_redir_is_next));
		return (1);
	}
	else if (*q == '<' && qt_opened == -1)
		lstadd_back_devide(deviders, \
								lstnew_devide(pos, back_redir_is_next));
	else if (*q == '>' && *(q + 1) == '>' && qt_opened == -1)
	{
		lstadd_back_devide(deviders, lstnew_devide(pos, double_redir_is_next));
		return (1);
	}
	else if (*q == '>' && qt_opened == -1)
		lstadd_back_devide(deviders, lstnew_devide(pos, redir_is_next));
	return (0);
}

t_deviders	*get_deviders_list(char *str)
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
		else if (str[i] != '\0' && str[i + 1] == '\"' && str[i] != '\\')
			qt_opened = find_next_quote(str, i, '\"');
		i += get_devider(&(str[i]), qt_opened, &pos, &deviders);
		pos++;
		i++;
	}
	return (deviders);
}
