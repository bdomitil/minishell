#include "../headers/minishell.h"

//void 	exec_rmfile(char **env, char *file)
//{
//	int		pid;
//	char	**args;
//
//	args = malloc(sizeof(char *) * 3);
//	if (!args)
//		terminate(strerror(errno));
//	args[0] = ft_strdup("rm\0");
//	args[1] = ft_strdup(file);
//	args[2] = NULL;
//	pid = fork();
//	if (pid == 0)
//	{
//		if (execve("/bin/rm\0", args, env) == -1)
//			terminate(strerror(errno));
//	} else
//		waitpid(pid, 0, 0);
//	free(args[0]);
//	free(args[1]);
//	free(args);
//}

//void	rm_here_docs(char **envp, t_parse_lst *lst)
//{
//	while (lst)
//	{
//		if (lst->stop_list && lst->stop_list->content)
//			exec_rmfile(envp, lst->stop_list->content);
//		lst = lst->next;
//	}
//}

//int	hd(t_parse_lst *lst, char *a)
//{
//	int			fd;
//	char		*line;
//	t_list 		*tmp;
//	char 		*filename;
//
//	tmp = lst->stop_list;
//	filename = NULL;
//	filename = ft_strjoin(ft_strjoin(filename, "./.heredoc"), a);
//	fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
//	while (tmp)
//	{
//		while (1)
//		{
//			get_next_line(0, &line);
//			if (!ft_strcmp(line, (char *)tmp->content))//, \ //ft_strlen((char *)tmp->content) + 1))
//			{
//				free(line);
//				break;
//			}
//			if (!tmp->next)
//			{
//				write(fd, line, ft_strlen(line));
//				free(line);
//				write(fd, "\n", 1);
//			}
//		}
//		tmp = tmp->next;
//	}
//	lst->stop_list->content = ft_strdup(filename);
//	write(fd, (void *)EOF, 4);
//	close (fd);
//	fd = open (filename, O_RDONLY);
//	free (filename);
//	return (fd);
//}

//
//void 	her (t_parse_lst *lst)
//{
//
//}
void	child_hd(int *pfd, t_parse_lst *lst)
{
	char	*line;
	t_list	*tmp;

	tmp = lst->stop_list;
	close (pfd[0]);
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

void wait_hd(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_exit_status = 0;
	if (WIFEXITED(status))
		if (status)
			g_exit_status = 1;
	if (WIFSIGNALED(status) != 0)
		g_exit_status = 128 + status;
}

int	*here_doc(t_parse_lst *lst, int *pfd)
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
	wait_hd(pid);// выставить сигналы как в родительском проц
	close(pfd[1]);
	lst->fd_in = pfd[0];
	return (true);
}