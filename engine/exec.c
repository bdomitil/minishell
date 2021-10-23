/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:54:59 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 14:28:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**envprint(t_env *env)
{
	char	**envarray;
	int		size = 1;
	t_env	*tmp_env;

	tmp_env = env;
	while (env)
	{
		size++;
		env = env->next;
	}
	envarray = (char **)malloc (sizeof(char *) * size);
	if (!envarray)
		return(NULL);
	size = 0;
	while (tmp_env)
	{
		envarray[size++] = ft_strdup(tmp_env->env_type);
		tmp_env = tmp_env->next;
	}
	envarray[size] = NULL;
	return (envarray);
}

int		exex(t_parse_lst **lst)
{

	pid_t		pid;
	t_exec_args	*tmp;

	tmp = array_it_all(*lst);
	if (!here_doc(*lst, tmp))
			return (0);
	pid = fork();
	if (pid == 0) // child
		actually_exec(*lst, tmp->cmd_and_args, tmp->env);
	(*lst)->pid = pid;
	freesh(tmp);
	return (1);
}

void 	freesh(t_exec_args *tmp)
{
	if (!tmp)
		return ;
	free_string_mass(tmp->cmd_and_args, 0, 0);
	free_string_mass(tmp->env, 0, 0);
	free(tmp->cmd_and_args);
	free(tmp->env);
	free (tmp);
}

void	actually_exec(t_parse_lst *lst, char **cmd_and_args, char **envp)
{
	if (!redir(lst) || !close_fds(lst))
		exit (errno);
	execve(lst->command, cmd_and_args, envp);
	if (errno == 2)
	{
		error_sh_cmd_msg(127, lst->command, NULL, \
		"command not found");
						 exit(127);
	}
	error_sh_cmd_msg(127, lst->command, NULL, \
	strerror(errno));
					 exit (errno);
}

t_exec_args *array_it_all(t_parse_lst *lst)
{
	t_args		*tmp_args;
	t_exec_args *tmp;

	if (lst)
		tmp_args = lst->args;
	tmp = (t_exec_args *) malloc(sizeof (t_exec_args));
	tmp->env = envprint(lst->env_lst);
	if (tmp_args)
		tmp->cmd_and_args = (char **)malloc(sizeof(char *) * \
		(tmp_args->tail->id + 3));
	else
		tmp->cmd_and_args = (char **)malloc(sizeof(char *) * 2);
	int i = 1;
	tmp->cmd_and_args[0] = ft_strdup(lst->command);
	while (tmp_args && i < tmp_args->tail->id + 2)
	{
		tmp->cmd_and_args[i] = ft_strdup(tmp_args->arg);
		tmp_args = tmp_args->next;
		i++;
	}
	tmp->cmd_and_args[i] = NULL;
	if (ft_strncmp("/", lst->command, 1))
		join_path(&(lst->command), lst->env_lst);
	return (tmp);
}