#ifndef PARSE_H
# define PARSE_H

# include "./types.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>

// # include "engine.h" // переделать

typedef struct t_msh
{
	int	g_exit_status;
	int	hd_return;
}	t_msh;

t_msh	g_mshl;

//||
//||
void		ft_shell_lst_add_back(t_parse_lst *lst, t_parse_lst *new_lst);
void		ft_args_lst_add_back(t_parse_lst *lst, t_args *new_lst);
int			parser(char **str, t_parse_lst **pars_lst, t_env *env_lst);
int			not_ending_string(char **str);//looks if string ends with not valid symbol | or ' or " 
char		*relese_quoutes(int i, char *str, t_env *env_lst);
char		*screen_chars(char *str, int open_uquote, int *i, t_env *env_lst);
int			find_next_quote(char *str, int i, char quote);
int			find_open_quote(char *str, int pos, char quote);
char		*get_var_mean(char *str, int *i, t_env *env_lst);
char		*cut_char(char *str, int char_pos);
char		**split_out_quotes(const char *str, char q);
int			fill_lst(char *str, t_parse_lst *pars_lst, t_env *env_lst);
t_args		*init_arg_lst(char *str);
t_parse_lst	*init_pars_lst(void);
t_deviders	*get_deviders_list(char *str);
void		print_pars_lst(t_parse_lst **lst);
int			get_redir_fd(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str);
void		free_dev_lst(t_deviders **devider);
int			parse_str(char **str, t_env *env_lst);
char		*get_file_name(char *str, char **to_ret_str, t_env *env_lst);
void		*free_string_mass(char **mass, int size, int use_size);
int			single_redir_fd(char **str, t_deviders *dev_lst, t_found type);
int			double_redir_fd(char **str, t_deviders *dev_lst, bool double_back, t_parse_lst *curr_pars);
t_env		*parse_env(char **env);
char		*find_env_key(t_env *env_lst, char *key);
char		*change_sh_lvl(char *shlvl);
void		commands_args_fill(t_parse_lst *current_pars, char **command_params, t_env *env_lst);
void		join_path(char **str, t_env *env_lst);
void		del_env_lst_by_key(t_env *env_lst, char *key);
void 		print_env_lst(t_env *env_lst);

#endif 