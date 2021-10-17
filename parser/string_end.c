/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 02:08:33 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/17 22:53:30 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static int	not_ending_help(char *str, int *i, int *next_quote, int slash)
{
	if (str[*i] == '\'' && (i == 0 || str[*i - 1] != '\\'))
	{
		*next_quote = find_next_quote(str, *i, '\'');
		if (*next_quote == -1)
			return (false);
		else
			*i = *next_quote;
	}
	else if (str[*i] == '\"' && (i == 0 || str[*i - 1] != '\\'))
	{
		*next_quote = find_next_quote(str, *i, '\"');
		if (*next_quote == -1)
			return (false);
		else
			*i = *next_quote;
	}
	else if (str[*i] == '|' && ft_isempty_str(&(str[*i + 1])))
		return (false);
	else if ((slash % 2) != 0 && str[*i] == '\\' && str[*i + 1] == '\0')
		return (false);
	return (true);
}

int	not_ending_string(char **str)
{
	int		i;
	int		next_quote;
	int		slash;

	next_quote = 0;
	i = -1;
	slash = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\\' && ((*str)[i + 1] != '\\' && \
		(*str)[i + 1] != '$' && (*str)[i + 1] != '\"' && (*str)[i + 1] != '\''\
		&& (i == 0 || (*str)[i - 1] != '\\') && (*str)[i + 1] != '\0'))
			(*str) = cut_char((*str), i);
		if ((*str)[i] == '\\')
			slash++;
		if (not_ending_help(*str, &i, &next_quote, slash) == false)
			return (false);
	}
	return (true);
}
