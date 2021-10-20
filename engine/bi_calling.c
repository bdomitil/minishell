#include "../headers/minishell.h"

static void choose_func(t_parse_lst *lst)
{
	if (lst->built_in == e_echo)
		ft_echo(lst);
	else if (lst->built_in == e_pwd)
		ft_pwd(lst);
	else if (lst->built_in == e_cd)
		ft_cd(lst);
//	else if (lst->built_in == e_export)
//		ft_export(lst);
	else if (lst->built_in == e_unset)
		ft_unset(lst);
	else if (lst->built_in == e_env)
		print_env_lst (lst->env_lst);
	else if (lst->built_in == e_exit)
		ft_exit(lst);
}

void	builtin_unar_call(t_parse_lst *lst)
{
	int fd_in;
	int fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	redir(lst);
	close_pipes(lst);
	choose_func(lst);
	if (dup2(fd_in, 0) == -1)
		terminate(strerror(errno));
	if (dup2(fd_out, 1) == -1)
		terminate(strerror(errno));
	close (fd_in), close (fd_out);
}

void	builtin_fork_call(t_parse_lst *lst)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		redir(lst);
		close_pipes(lst);
		choose_func(lst);
		exit (0);
	}
	else
		lst->pid = pid;
}