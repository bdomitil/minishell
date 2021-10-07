#include "../headers/minishell.h"

void	get_fd_of_hd(t_parse_lst *lst)
{
	int	pfd[2];
	int	pid;

	pipe(pfd);
	lst->fd_out = pfd[0];
	pid = fork();
	if (!pid)
	{
		close_pipes(lst);
		close(pfd[0]);
		while (*lst->here_doc)
		{
			write(pfd[1], *lst->here_doc, ft_strlen(*lst->here_doc));
			write(pfd[1], "\n", 1);
			lst->here_doc++;
		}
		write(pfd[1], (void *)EOF, 4); // может ломать
		exit (0);
	}
	else
	{
		dup2(lst->fd_out, 0); //  вопрос
		close (pfd[0]), close(pfd[1]);
	}
}

//void	hdd(t_parse_lst *lst)
//{
//	char 	*string;
//	int 	res;
//
//	while (lst->stop_list)
//	{
//		res = get_next_line(0, &string);
//		lst->here_doc = NULL;
//		while (res >= 0)
//		{
//			if (ft_strncmp(string, (char *)lst->stop_list->content, \
//			ft_strlen(string)))
//				break;
//			if (!lst->stop_list->next)
//			{
//				lst->here_doc = arrjoin(lst->here_doc, string);
//				res = get_next_line(0, &string);
//			}
//		}
//		lst->stop_list = lst->stop_list->next;
//	}
//}

//-------check_here_doc-------
void	hd(t_parse_lst *lst)
{
	if (!lst)
		return;
	char *string;
	int res;
//-----------------------
	char **args;
	args = malloc(sizeof(char *) * 3);
	args[0] = malloc(sizeof(char) * 4);
	args[0] = "s\0";
	args[1] = "t\0";
	args[2] = NULL;
//-----------------------
	while (*args)
	{
		res = get_next_line(0, &string);
		lst->here_doc = NULL;

		while (res >= 0)
		{
			if (!ft_strncmp(string, *args, ft_strlen(string)))
				break;
			if (!lst->stop_list->next)
			{
				lst->here_doc = arrjoin(lst->here_doc, string);
				res = get_next_line(0, &string);
			}
		}
//		write (1, *args, 20);
		(args)++;
//		write (1, *args, 20);
	}
}
//--------------------------