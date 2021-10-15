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


void	redir(t_parse_lst *lst);
void	io_pipes(t_parse_lst *lst);
void	exex(t_parse_lst **lst);
void	close_pipes(t_parse_lst *lst);
void	clean_main_list(t_parse_lst *lst);
void	exe_built_in(t_parse_lst *lst);
char	**arrjoin(char **arr, char *str);
void	get_fd_of_hd(t_parse_lst *lst);
char	**envprint(t_env *env);
void 	ft_echo(t_parse_lst *lst);
void 	ft_pwd(t_parse_lst *lst);
void	ft_cd(t_parse_lst *lst);
void	ft_export(t_parse_lst *lst);
void	change_PWD(t_parse_lst *lst);
//-----------
char	*get_OLDPWD(t_parse_lst *lst);
char	*get_PWD(t_parse_lst *lst);
char	*get_HOME(t_parse_lst *lst);
//-----------
void	ft_unset(t_parse_lst *lst);
int 	hd(t_parse_lst *lst, char *a);
void	rm_here_docs(char **envp, t_parse_lst *lst);
char	**envprint(t_env *env);

#endif
