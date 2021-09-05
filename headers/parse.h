#ifndef PARSE_HEADER_H
# define PARSE_HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>

typedef enum e_types_of_found
{
	pipe_is_next,
	redir_is_next,
	double_redir_is_next,
	back_redir_is_next,
	double_back_redir_is_next,
	none
}				t_found;


typedef struct s_parsed_args
{
	struct s_parsed_args	*next;
	struct s_parsed_args	*previous;
	struct s_parsed_args	*head;
	struct s_parsed_args	*tail;
	char					*arg;
}				t_args;

typedef struct s_main_parse_list
{
	struct s_main_parse_list	*head;
	struct s_main_parse_list	*tail;
	struct s_main_parse_list	*next;
	struct s_main_parse_list	*previous;
	t_args						*args;
	// t_found						type_of_next_command;
	bool						pipe;
	bool						redir_in;
	bool						redir_out;
	int							file_fd;
	int							exit_status;
	char						*command;

}		t_parse_lst;

typedef struct	s_spec_deviders
{
	t_found	type;
	int		pos_in_str;
	struct	s_spec_deviders *next;
}				t_deviders;
//||
//||
void		ft_shell_lst_add_back(t_parse_lst *lst, t_parse_lst *new_lst);
void		ft_args_lst_add_back(t_parse_lst *lst, t_args *new);
int			parser(char **str, t_parse_lst **pars_lst);
int			not_ending_string(char **str);//looks if string ends with not valid symbol | or ' or " 
char		*relese_quoutes(char *str, t_parse_lst *pars_lst);
char		*screen_chars(char *str, int open_uquote, int *i, t_parse_lst *pars_lst);
int			find_next_quote(char *str, int i, char quote);
int			find_open_quote(char *str, int pos, char quote);
char		*get_var_mean(char *str, t_parse_lst *pars_lst, int *i);
char		*cut_char(char *str, int char_pos);
char		**split_out_quotes(const char *str, char q);
int			fill_lst(char *str, t_parse_lst *pars_lst);
t_args		*init_arg_lst(void);
t_parse_lst	*init_pars_lst(void);
t_deviders	*get_deviders_list(char *str);
void		print_pars_lst(t_parse_lst **lst);
int			get_redir_fd(t_found type, t_parse_lst *curr_pars, char *filename);

#endif 