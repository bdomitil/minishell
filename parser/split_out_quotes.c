/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_out_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 01:40:45 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/20 20:29:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static	int	count_word(const char *str, char q)
{
	int		i;
	int		num;
	int		d_qt;
	int		s_qt;

	i = 0;
	d_qt = 2;
	s_qt = 2;
	num = 0;
	str = ft_strtrim(str, &q);
	while (str[i])
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			d_qt++;
		else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			s_qt++;
		if (str[i] == q && (str[i + 1] != q && ft_isprint(str[i + 1])) \
												&& !(d_qt % 2) && !(s_qt % 2))
				num++;
		i++;
	}
	free((void *) str);
	return (num + 1);
}


static	int	get_len(const char *str, char q)
{
	int		i;
	int		d_qt;
	int		s_qt;

	i = 0;
	d_qt = 2;
	s_qt = 2;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			d_qt++;
		else if(str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			s_qt++;
		if ((str[i] == q || !ft_isprint(str[i])) && !(d_qt % 2)  && !(s_qt % 2))
		{
			i += (str[i] == '\"' || str[i] == '\'');
			break ;
		}
		i++;
	}
	return (i);
}

static	char	*get_next_word(const char *str, char q)
{
	int		len;
	char	*word;

	while (*str != '\0' && (*str == q || !ft_isprint(*str)))
		str++;
	len = get_len(str, q);
	word = ft_substr(str, 0, len);
	if (!word)
		return (NULL);
	return (word);
}

static void	ft_free(char **mass, int pos)
{
	while (pos >= 0)
		free(mass[pos--]);
	free(mass);
}

char	**split_out_quotes(const char *str, char q)
{
	int		word_num;
	int		i;
	char	**to_ret;

	i = 0;
	to_ret = NULL;
	if (!str)
		return (NULL);
	word_num = count_word(str, q);
	to_ret = malloc((word_num + 1) * sizeof(char *));
	if (!to_ret)
		return (NULL);
	while (i < word_num)
	{
		to_ret[i] = get_next_word(str, q);
		if (!to_ret[i])
		{
			ft_free(to_ret, i);
			return (NULL);
		}
		str += ft_char_index(str, to_ret[i][0]) + ft_strlen(to_ret[i]);
		i++;
	}
	to_ret[word_num] = NULL;
	return (to_ret);
}
