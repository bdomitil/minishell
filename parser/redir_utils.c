/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:09:51 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/20 20:29:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

int	single_redir_fd(char **str, t_deviders *dev_lst, t_found type)
{
	int		i;
	char	*file_name;
	int		fd;
	char	*tmp_str;

	i = 0;
	tmp_str = *str;
	(*str)[dev_lst->pos_in_str] = ' ';
	if (ft_isempty_str(&((*str)[dev_lst->pos_in_str + 1])))
		return (-1);
	while ((*str)[dev_lst->pos_in_str + ++i] != '\0' \
							&& !ft_isprint((*str)[dev_lst->pos_in_str + i]))
		if ((*str)[dev_lst->pos_in_str + i] == '|' || (*str) \
	[dev_lst->pos_in_str + i] == '>' || (*str)[dev_lst->pos_in_str + i] == '<')
			return (-1);
	file_name = get_file_name(&((*str)[dev_lst->pos_in_str + 1]), \
														str, dev_lst->env_lst);		
	if (!file_name)
		return (-1);
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
	return (to_ret);
}

int	double_redir_fd(char **str, t_deviders *dev_lst, \
									bool double_back, t_parse_lst *curr_pars)
{
	int		i;
	char	*file_name;
	int		fd;

	i = 0;
	fd = -2;
	(*str)[dev_lst->pos_in_str] = ' ';
	*str = cut_char(*str, dev_lst->pos_in_str - 1);
	if (ft_isempty_str(&((*str)[dev_lst->pos_in_str + 1])))
		return (-1);
	while ((*str)[dev_lst->pos_in_str + ++i] != '\0' && \
								!ft_isprint((*str)[dev_lst->pos_in_str + i]))
		if ((*str)[dev_lst->pos_in_str + i] == '|' || (*str) \
	[dev_lst->pos_in_str + i] == '>' || (*str)[dev_lst->pos_in_str + i] == '<')
			return (-1);
	file_name = get_file_name(&((*str)[dev_lst->pos_in_str]), \
												str, dev_lst->env_lst);
	if (!file_name)
		return (-1);
	if (!double_back)
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		ft_lstadd_back(&(curr_pars->stop_list), ft_lstnew((void *)ft_strdup(file_name)));
	free(file_name);
	return (fd);
}

static char	*make_file_name(char **to_ret_str, char *str, int i, t_env *env_lst)
{
	char	*file_name;
	bool	to_join;
	char	*tmp;
	char	tmp_char;

	tmp_char = str[i];
	to_join = str[i];
	(void)env_lst;
	file_name = NULL;
	if (str[i] != '\0')
		str[i] = '\0';
	if (*str == '$')
		file_name = ft_strdup(find_env_key(env_lst, str + 1));
	else
		file_name = ft_strdup(relese_quoutes(0, str, env_lst));
	*str = '\0';
	str[i] = tmp_char;
	if (to_join)
	{
		tmp = *to_ret_str;
		*to_ret_str = ft_strjoin(*to_ret_str, &(str[i])), free(tmp);
	}
	else
		(*to_ret_str)[ft_strlen(*to_ret_str)] = '\0';
	return (file_name);
}

char	*get_file_name(char *str, char **to_ret_str, t_env *env_lst)
{
	char	*file_name;
	int		i;
	int		qt;

	i = 0;
	qt = 1;
	while (!ft_isprint(*str))
		str++;
	while ((ft_isprint(str[i]) && str[i] != '<' \
						&& str[i] != '>' && str[i] != '|') || qt % 2 == 0)
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			qt++;
		i++;
	}
	file_name = make_file_name(to_ret_str, str, i, env_lst);
	return (file_name);
}
