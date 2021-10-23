/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:39:19 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:58:00 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ultra_pipex(t_parse_lst *lst)
{
	while (lst)
	{
		if (lst->built_in)
		{
			if (lst->next || lst->previous)
				builtin_fork_call(lst);
			else
				builtin_unar_call(lst);
		}
		else
		{
			exex_sign_redif();
			exex(&lst);
		}
		lst = lst->next;
	}
}

static void	minishell(t_parse_lst *lst, t_env *env_lst)
{
	char	*str;

	while (1)
	{
		str = readline("mini$heeee$h-1.0$ ");
		if (!str)
			exit(g_mshl.g_exit_status);
		if (ft_strcmp(str, "\0"))
			add_history(str);
		if (parser(&str, &lst, env_lst) == -1)
			exit_print(&lst, true);
		else if (lst)
		{
			io_pipes(lst);
			ultra_pipex(lst);
			exit_print(&lst, false);
			parent_sign_redif();
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_parse_lst	*lst;
	t_parse_lst	*head;
	t_env		*env_lst;

	lst = NULL;
	head = NULL;
	rl_outstream = stderr;
	(void)argc, (void)argv;
	if (env)
		env_lst = parse_env(env);
	parent_sign_redif();
	g_mshl.g_exit_status = 0;
	minishell(lst, env_lst);
	return (0);
}
