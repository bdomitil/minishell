#ifndef ENGINE_H
# define ENGINE_H
# include "types.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>


void	redir(t_parse_lst **lst);
void	io_pipes(t_parse_lst *lst);
void	exex(t_parse_lst **lst);
void	close_pipes(t_parse_lst *lst);

#endif