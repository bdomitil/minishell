#include "../headers/minishell.h"

void	child_hd(int *pfd, t_parse_lst *lst)
{
	char	*line;
	t_list	*tmp;

	tmp = lst->stop_list;
	close (pfd[0]);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_heredoc);
	while (tmp)
	{
		while (1)
		{
			line = readline("> ");
			if (!ft_strcmp(line, (char *) tmp->content))
			{
				free(line);
				break;
			}
			if (!tmp->next)
			{
				write(pfd[1], line, ft_strlen(line));
				free(line);
				write(pfd[1], "\n", 1);
			}
		}
		tmp = tmp->next;
	}
}

bool	here_doc(t_parse_lst *lst, int *pfd)
{
	pid_t pid;

	if (pipe(pfd) == -1)
	{
		error_sh_cmd_msg(1, "pipe", NULL, strerror(errno));
		return (false);
	}
	pid = fork();
	if (pid == -1)
	{
		error_sh_cmd_msg(1, "fork", NULL, strerror(errno));
		return (false);
	}
	// сюда сигнал
	if (!pid)
	{
		child_hd(pfd, lst);
		write(pfd[1], (void *)EOF, 4);
		close (pfd[1]);
		exit(0);
	}
	// сюда сигнал
	if (!wait_process(pid))
		return (false);// выставить сигналы как в родительском проц
	signal(SIGQUIT, ctrl_slsh);
	close(pfd[1]);
	lst->fd_in = pfd[0];
	return (true);
}