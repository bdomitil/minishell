#ifndef TYPES_H
# define TYPES_H
# include <stdbool.h>
# include "libft.h"

typedef enum e_types_of_found
{
	pipe_is_next,
	redir_is_next,
	double_redir_is_next,
	back_redir_is_next,
	double_back_redir_is_next,
	none
}				t_found;

typedef enum e_built_in
{
	ft_echo = 1,
	ft_cd,
	ft_pwd,
	ft_export,
	ft_unset,
	ft_env,
	ft_exit
}				t_built_in;

typedef struct	s_env
{
	struct s_env	*next;
	char			*value;
	char			*env_type;
	char			*key;
}				t_env;

typedef struct s_parsed_args
{
	struct s_parsed_args	*next;
	struct s_parsed_args	*previous;
	struct s_parsed_args	*head;
	struct s_parsed_args	*tail;
	int						id; // выпилить id
	char					*arg;
}				t_args;

typedef struct s_main_parse_list
{
	struct s_main_parse_list	*head;
	struct s_main_parse_list	*tail;
	struct s_main_parse_list	*next;
	struct s_main_parse_list	*previous;
	t_env						*env_lst;
	t_args						*args;
	t_list						*stop_list;
	bool						pipe;
	int 						built_in;
	int							fd_in;
	int							fd_out;
	int 						pid;
	int							exit_status;
	char						*command;
	char						**here_doc;

}		t_parse_lst;

//typedef void	(*func)(t_parse_lst *lst);
//typedef	func t_func;

typedef struct	s_spec_deviders
{
	t_found	type;
	int		pos_in_str;
	t_env	*env_lst;
	struct	s_spec_deviders *next;
}				t_deviders;

#endif