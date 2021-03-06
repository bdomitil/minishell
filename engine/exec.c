/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:54:59 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 21:26:35 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/engine.h"

char	**envprint(t_env *env)
{
	char	**envarray;
	int		size;
	t_env	*tmp_env;

	size = 1;
	tmp_env = env;
	while (env)
	{
		size++;
		env = env->next;
	}
	envarray = (char **)malloc (sizeof(char *) * size);
	if (!envarray)
		return (NULL);
	size = 0;
	while (tmp_env)
	{
		envarray[size++] = key_value(tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	envarray[size] = NULL;
	return (envarray);
}

int	exex(t_parse_lst **lst)
{
	pid_t		pid;
	t_exec_args	*tmp;

	tmp = array_it_all(*lst);
	if (!here_doc(*lst, tmp))
		return (0);
	pid = fork();
	if (pid == 0)
		actually_exec(*lst, tmp->cmd_and_args, tmp->env);
	(*lst)->pid = pid;
	freesh(tmp);
	return (1);
}

void	freesh(t_exec_args *tmp)
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
	int	exec_error;

	exec_error = 0;
	if (!redir(lst) || !close_fds(lst))
		exit(errno);
	exec_error = execve(lst->command, cmd_and_args, envp);
	if (errno == 2 && exec_error == -1)
	{
		error_sh_cmd_msg(127, lst->command, NULL, \
		"command not found");
		exit(127);
	}
	else if (exec_error == -1 && errno != 13)
	{
		error_sh_cmd_msg(127, lst->command, NULL, \
		strerror(errno));
		exit(errno);
	}
	else if (errno == 13)
		exit(errno);
}

t_exec_args	*array_it_all(t_parse_lst *lst)
{
	t_args		*tmp_args;
	t_exec_args	*tmp;
	int			i;

	tmp_args = NULL;
	if (lst)
		tmp_args = lst->args;
	tmp = (t_exec_args *) malloc(sizeof (t_exec_args));
	tmp->env = envprint(lst->env_lst);
	if (tmp_args)
		tmp->cmd_and_args = (char **)malloc(sizeof(char *) * \
		(tmp_args->tail->id + 3));
	else
		tmp->cmd_and_args = (char **)malloc(sizeof(char *) * 2);
	i = 1;
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
