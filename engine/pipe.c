#include "../headers/parse.h"

void close_pipes(t_parse_lst *lst)
{
	t_parse_lst *tmp_lst;

	tmp_lst = lst;
//	printf("cowcow\n");
	while (lst)
	{
	    if (lst->fd_in != 1)
	        close (lst->fd_in);
	    if (lst->fd_out != 0)
	        close (lst->fd_out);
		lst = lst->next;
	}
	lst = tmp_lst;
	while (lst)
	{
	    if (lst->fd_in != 1)
	        close (lst->fd_in);
	    if (lst->fd_out != 0)
	        close (lst->fd_out);
		lst = lst->previous;
	}
}