/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:09:51 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 04:53:24 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

int	single_redir_fd(char **str, int pos_in_str, t_found type)
{
	int		i;
	char	*file_name;
	int		fd;
	char	*tmp_str;

	i = 0;
	tmp_str = *str;
	(*str)[pos_in_str] = ' ';
	if (ft_isempty_str(&((*str)[pos_in_str + 1])))
		return(-1);
	while ((*str)[pos_in_str + ++i] != '\0' \
									&& !ft_isalpha((*str)[pos_in_str + i]))
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
	free(file_name);
	return (fd);
}

char	*join_stop_words(char *old_stop_word, char *new_stop_word)
{
	char	*tmp_word;
	char	*to_ret;

	to_ret = ft_strjoin(old_stop_word, "_");
	free(old_stop_word);
	tmp_word = to_ret;
	to_ret = ft_strjoin(to_ret, new_stop_word);
	free(tmp_word);
	return(to_ret);
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
	(*str)[pos_in_str] = ' ';
	*str = cut_char(*str, pos_in_str - 1);
	if (ft_isempty_str(&((*str)[pos_in_str + 1])))
		return(-1);
	while ((*str)[pos_in_str + ++i] != '\0' && !ft_isalpha((*str)[pos_in_str + i]))
		if ((*str)[pos_in_str + i] == '|' || \
		(*str)[pos_in_str + i] == '>'|| (*str)[pos_in_str + i] == '<')
			return(-1);
	file_name = get_file_name(&((*str)[pos_in_str]), str);
	if (!file_name)
		return(-1);
	if (!double_back)
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		curr_pars->stop_word = join_stop_words(curr_pars->stop_word, file_name);
	free(file_name);
	return (fd);
}


static char	*make_file_name(char **to_ret_str, char *str, int i, char tmp_char)
{
	char	*file_name;
	bool	to_join;
	char	*tmp;

	to_join = false;
	file_name = NULL;
	if (str[i] != '\0')
	{
		str[i] = '\0';
		to_join = true;
	}
	if (*str == '$')
		file_name = ft_strdup(getenv(str + 1));
	else
		file_name = ft_strdup(relese_quoutes(str));
	*str = '\0';
	str[i] = tmp_char;
	if (to_join)
	{
		tmp = *to_ret_str;
		*to_ret_str = ft_strjoin(*to_ret_str, &(str[i]));
		free(tmp);
	}
	else
		(*to_ret_str)[ft_strlen(*to_ret_str)] = '\0';
	return (file_name);
}

char	*get_file_name(char *str, char **to_ret_str)
{
	char	*file_name;
	int		i;
	int		qt;

	i = 0;
	qt = 1;
	while (!ft_isprint(*str))
		str++;
	while ((ft_isprint(str[i]) && str[i] != '<' \
									&& str[i] != '>') || qt % 2 == 0)
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			qt++;
		i++;
	}
	file_name = make_file_name(to_ret_str, str, i, str[i]);
	return (file_name);
}
