/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:35:39 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/21 17:35:49 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

size_t	ft_ft_strlen(const char *str)
{
	size_t	i;

	i = 1;
	while (*str++)
		i++;
	return (i);
}

int	find_next_quote(char *str, int i, char quote)
{
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == quote && str[i - 1] != '\\')
			return (i);
		i++;
	}
	 return (-1);
}

static char	*cut_quotes(char **str, int *open, int *close)
{
	(*str)[*open] = 0;
	(*str)[*close] = 0;
	ft_memmove(&(*str)[*close], &(*str)[*close + 1], \
											ft_ft_strlen(&(*str)[*close + 1]));
	ft_memmove(&(*str)[*open], &(*str)[*open + 1], \
											ft_ft_strlen(&(*str)[*open + 1]));
	*open = -1;
	return (*str);
}

static void	slash_dollar(char **str, int *i)
{
	if ((*str)[*i] == '$' && (*i == 0 || (*str)[*i - 1] != '\\') && \
			(ft_isalpha((*str)[*i + 1]) || (*str)[*i + 1] == '?'))
		*str = get_var_mean((*str), i);
	else if ((*str)[*i] == '\\' && ((*str)[*i + 1] == '\\' || \
	(*str)[*i + 1] == '$' || (*str)[*i + 1] == '\'' || (*str)[*i + 1] == '\"'))
	{
		(*str) = cut_char((*str), *i);
		(*i)++;
	}
	else
		(*i)++;
}

char	*relese_quoutes(int i, char *str)
{
	int	quotes[4];

	ft_memset((void *)&quotes, -1, 4);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\') \
														&& quotes[1] == -1)
		{
			quotes[2] = i;
			quotes[3] = find_next_quote(str, i, '\'');
			i = quotes[3];
			str = cut_quotes(&str, &(quotes[2]), &quotes[3]);
		}
		else if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\') \
															&& quotes[3] == -1)
		{
			quotes[0] = i;
			str = screen_chars(str, quotes[0], &i);
			quotes[1] = i;
			str = cut_quotes(&str, &(quotes[0]), &quotes[1]);
		}
		else
			slash_dollar(&str, &i);
	}
	return (str);
}
