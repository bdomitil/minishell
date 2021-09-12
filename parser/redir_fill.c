/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 00:26:54 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/12 22:29:37 by bdomitil         ###   ########.fr       */
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
	*to_ret_str = ft_strjoin(*to_ret_str, &(str[i + 1]));
	// free(tmp_word);
	return (file_name);
}

int	one_redir_fd(char **str, int pos_in_str, t_found type)
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
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (type == back_redir_is_next)
		fd = open(file_name, O_RDONLY);
	(*str)[pos_in_str] = ' ';
	free(file_name);
	return (fd);
}

int	get_fd_out(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_out;
	t_deviders	*tmp_dev;

	fd_out = -1;
	while ((*dev_lst) && (*dev_lst)->type == back_redir_is_next)
	{
		close(fd_out);
		fd_out = one_redir_fd(str, (*dev_lst)->pos_in_str, (*dev_lst)->type);
		if (fd_out == -1)
			return(0);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		curr_pars->fd_out = fd_out;
		free(tmp_dev);
	}
	return (1);
}

int	get_fd_in(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int			fd_in;
	t_deviders	*tmp_dev;

	fd_in = -1;
	while ((*dev_lst) && (*dev_lst)->type == redir_is_next)
	{
		close(fd_in);
		fd_in = one_redir_fd(str, (*dev_lst)->pos_in_str, (*dev_lst)->type);
		if (fd_in == -1)
			return(0);
		tmp_dev = *dev_lst;
		*dev_lst = get_deviders_list(*str);
		curr_pars->fd_in= fd_in;
		free(tmp_dev);
	}
	return (1);
}

int	get_redir_fd(t_parse_lst *curr_pars, t_deviders **dev_lst, char **str)
{
	int res;

	res = 0;
	if ((*dev_lst)->type == redir_is_next)
		res = get_fd_in(curr_pars, dev_lst, str);
	else if ((*dev_lst)->type == back_redir_is_next)
		res = get_fd_out(curr_pars, dev_lst, str);
	return(res);
}