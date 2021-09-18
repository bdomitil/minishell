/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 00:26:54 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/19 02:37:31 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

char *get_file_name(char *str, char **to_ret_str)
{
	char	*file_name;
	int		i;
	char	*tmp_word;

	i = 0;
	tmp_word = str;
	file_name = NULL;
	while (!ft_isprint(*str))
		str++;
	while(ft_isprint(str[i]))
		i++;
	str[i] = '\0';
	if (*str == '$')
		file_name = ft_strdup(getenv(str + 1));
	else
		file_name = ft_strdup(str);
	*tmp_word = '\0';
	tmp_word = *to_ret_str;
	if (ft_isprint (str[i + 1]))
	{
		*to_ret_str = ft_strjoin(*to_ret_str, &(str[i + 1]));
		free(tmp_word);
	}
	return (file_name);
}

int	single_redir_fd(char **str, int pos_in_str, t_found type)
{
	int		i;
	char	*file_name;
	int		fd;
	char	*tmp_str;

	i = 0;
	tmp_str = *str;
	if (ft_isempty_str(&((*str)[pos_in_str + 1])))
		return(-1);
	while ((*str)[pos_in_str + ++i] != '\0' && !ft_isalpha((*str)[pos_in_str + i]))
		if ((*str)[pos_in_str + i] == '|' || \
		(*str)[pos_in_str + i] == '>'|| (*str)[pos_in_str + i] == '<')
			return(-1);
	file_name = get_file_name(&((*str)[pos_in_str + 1]), str);
	if (!file_name)
		return(-1);
	if (type == redir_is_next)
		fd = open(file_name, O_CREAT | O_WRONLY, 0777);
	if (type == back_redir_is_next)
		fd = open(file_name, O_RDONLY);
	(*str)[pos_in_str] = ' ';
	free(file_name);
	return (fd);
}

int	double_redir_fd(char **str, int pos_in_str, \
									bool double_back, t_parse_lst *curr_pars)
{
	int		i;
	char	*file_name;
	int		fd;
	char	*tmp_str;

	i = 0;
	tmp_str = curr_pars->stop_word;
	fd = -1;
	if (ft_isempty_str(&((*str)[pos_in_str + 1])))
		return(-1);
	while ((*str)[pos_in_str + ++i] != '\0' && !ft_isalpha((*str)[pos_in_str + i]))
		if ((*str)[pos_in_str + i] == '|' || \
		(*str)[pos_in_str + i] == '>'|| (*str)[pos_in_str + i] == '<')
			return(-1);
	file_name = get_file_name(&((*str)[pos_in_str + 1]), str);
	if (!file_name)
		return(-1);
	if (!double_back)
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		{
			curr_pars->stop_word = ft_strjoin(tmp_str, "\n");
			free(tmp_str);
			tmp_str = curr_pars->stop_word;
			curr_pars->stop_word = ft_strjoin(tmp_str, file_name);
			free(tmp_str);
		}
	(*str)[pos_in_str] = ' ';
	*str = cut_char(*str, pos_in_str - 1);
	free(file_name);
	return (fd);
}

int	get_fd_out(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_out;
	t_deviders	*tmp_dev;

	fd_out = -1;
	while ((*dev_lst) && ((*dev_lst)->type == back_redir_is_next \
								|| (*dev_lst)->type == double_back_redir_is_next))
	{
		close(fd_out);
		if ((*dev_lst)->type == back_redir_is_next)
			fd_out = single_redir_fd(str, (*dev_lst)->pos_in_str, (*dev_lst)->type);
		else
			double_redir_fd(str, (*dev_lst)->pos_in_str, true, curr_pars);	
		if (curr_pars->fd_in == -1 || fd_out == -1)
			return(-1);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		curr_pars->fd_out = fd_out;
		// free_dev_lst(dev_lst);
	}
	return (1);
}



int	get_fd_in(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_in;
	t_deviders	*tmp_dev;

	fd_in = -1;
	while ((*dev_lst) && ((*dev_lst)->type == redir_is_next || \
						(*dev_lst)->type == double_redir_is_next))
	{
		if (fd_in != -1)
			close(fd_in);
		if ((*dev_lst)->type == redir_is_next)
			fd_in = single_redir_fd(str, (*dev_lst)->pos_in_str, (*dev_lst)->type);
		else
			fd_in = double_redir_fd(str, (*dev_lst)->pos_in_str, false, curr_pars);		
		if (curr_pars->fd_out == -1 || fd_in == -1)
			return(-1);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		curr_pars->fd_in= fd_in;
		// free_dev_lst(dev_lst);
	}
	return (1);
}

int	get_redir_fd(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int res;

	res = 0;
	while ((*dev_lst) && (*dev_lst)->type != pipe_is_next \
		&& (*dev_lst)->type != none && res != -1)
	{
		if ((*dev_lst)->type == redir_is_next || \
												(*dev_lst)->type == double_redir_is_next)
			res = get_fd_in(curr_pars, dev_lst, str);
		else if ((*dev_lst)->type == back_redir_is_next || \
											(*dev_lst)->type == double_back_redir_is_next)
			res = get_fd_out(curr_pars, dev_lst, str);
	}
	return(res);
}