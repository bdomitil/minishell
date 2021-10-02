#include "../headers/parse.h"

void close_pipes(t_parse_lst *lst)
{
	t_parse_lst *tmp_lst;

	tmp_lst = lst;
//	printf("cowcow\n");
	while (lst)
	{
		if (lst != tmp_lst)
		{
			if (lst->next)
				close (lst->fd_in);
			if (lst->previous)
				close (lst->fd_out);
		}
		lst = lst->next;
	}
	lst = tmp_lst;
	while (lst)
	{
		if (lst != tmp_lst)
		{
			if (lst->next)
				close (lst->fd_in);
			if (lst->previous)
				close (lst->fd_out);
		}
		lst = lst->previous;
	}
}