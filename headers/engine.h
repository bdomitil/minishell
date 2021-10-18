#ifndef ENGINE_H
# define ENGINE_H
# include "types.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h> // strerror
# include <errno.h> // err macros
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>


void		redir(t_parse_lst *lst);
void		io_pipes(t_parse_lst *lst);
void		exex(t_parse_lst **lst);
void		close_pipes(t_parse_lst *lst);
void		clean_main_list(t_parse_lst *lst);
char		**arrjoin(char **arr, char *str);
void		get_fd_of_hd(t_parse_lst *lst);
char		**envprint(t_env *env);
/*
 * built-in
 */
void		builtin_unar_call(t_parse_lst *lst);
void		builtin_fork_call(t_parse_lst *lst);
void 		ft_echo(t_parse_lst *lst);
void		ft_pwd(t_parse_lst *lst);
void		ft_export(t_parse_lst *lst);
void 		ft_cd(t_parse_lst *lst);
void		ft_unset(t_parse_lst *lst);
//
int 		hd(t_parse_lst *lst, char *a);
void		rm_here_docs(char **envp, t_parse_lst *lst);
char		**envprint(t_env *env);
void		add_env_back(t_env **env_lst, char *key, char *value, char *env_type);
bool		change_value(t_env *env_lst, char *value, char *key);
extern void rl_replace_line(const char *, int);
/*
 * error handle
 */
int			error_sh_cmd_msg(int exit_status, char *cmd, char *arg, char *message);
void		ft_exit(t_parse_lst *lst);
/*
 * signal
 */
void	ctrl_c(int signal);
void	ctrl_c_forked(int signal);

#endif
