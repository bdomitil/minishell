/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:21:46 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:32:52 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include "types.h"
# include "parse.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

bool		redir(t_parse_lst *lst);
void		io_pipes(t_parse_lst *lst);
int			exex(t_parse_lst **lst);
void		actually_exec(t_parse_lst *lst, char **cmd_and_args, char **envp);
t_exec_args	*array_it_all(t_parse_lst *lst);
void		freesh(t_exec_args *tmp);
bool		close_fds(t_parse_lst *lst);
void		clean_main_list(t_parse_lst *lst);
char		**envprint(t_env *env);
void		exit_print(t_parse_lst **lst, bool parse_error);
/*
 * built-in
 */
void		builtin_unar_call(t_parse_lst *lst);
void		builtin_fork_call(t_parse_lst *lst);
void		ft_echo(t_parse_lst *lst);
void		ft_pwd(t_parse_lst *lst);
void		ft_export(t_parse_lst *lst);
void		check_plus(t_env *env_lst, char *value, char *key, bool plus);
void		ft_env(t_env *env_lst);
bool		valid_export_arg(char *tmp);
void		ft_cd(t_parse_lst *lst);
char		*cd_no_args(t_parse_lst *lst);
void		cd_change_env(t_parse_lst *lst, char *pwd);
void		ft_unset(t_parse_lst *lst);
/*
 * here DOC
 */
bool		hd_exec(t_parse_lst *lst, int *pfd);
bool		here_doc(t_parse_lst *lst, t_exec_args *tmp);
void		rm_here_docs(char **envp, t_parse_lst *lst);
char		**envprint(t_env *env);
void		add_env_back(t_env **env_lst, char *key, char *value, \
			char *env_type);
bool		change_value(t_env *env_lst, char *value, char *key, bool plus);
extern void	rl_replace_line(const char *s, int i);
/*
 * error handle
 */
void		error_sh_cmd_msg(int exit_status, char *cmd, \
			char *arg, char *message);
void		ft_exit(t_parse_lst *lst);
/*
 * signal
 */
void		ctrl_c(int signal);
void		ctrl_slsh(int signal);
void		ctrl_c_forked(int signal);
void		ctrl_c_heredoc(int signal);
void		parent_sign_redif(void);
void		exex_sign_redif(void);
void		hd_sig_redif(void);
/*
 * wait
 */
bool		wait_process(t_parse_lst *lst);
void		while_wait(t_parse_lst *lst);

#endif
