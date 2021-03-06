/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:36:01 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:38:28 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	e_echo = 1,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit
}				t_built_in;

typedef struct s_env
{
	struct s_env	*next;
	char			*value;
	char			*env_type;
	char			*key;
	bool			visible;
}				t_env;

typedef struct s_parsed_args
{
	struct s_parsed_args	*next;
	struct s_parsed_args	*previous;
	struct s_parsed_args	*head;
	struct s_parsed_args	*tail;
	int						id;
	char					*arg;
}				t_args;

typedef struct s_exec_args
{
	char	**cmd_and_args;
	char	**env;

}				t_exec_args;

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
	int							built_in;
	int							fd_out;
	int							fd_in;
	int							pid;
	int							exit_status;
	char						*command;
}				t_parse_lst;

typedef struct s_spec_deviders
{
	t_found						type;
	int							pos_in_str;
	t_env						*env_lst;
	struct s_spec_deviders		*next;
}				t_deviders;

#endif