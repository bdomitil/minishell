/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:15:23 by frodney           #+#    #+#             */
/*   Updated: 2021/10/23 19:07:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static bool	valid_key(char *key)
{
	if (!key)
		return (false);
	while (*key)
	{
		if (*key == 38 || *key == 33 || !ft_isascii(*key))
			return (false);
		key++;
	}
	return (true);
}

static bool	valid_value(char *value)
{
	if (!value)
		return (true);
	value++;
	while (*value)
	{
		if (*value == 38 || *value == 33 || !ft_isascii(*value))
			return (false);
		value++;
	}
	return (true);
}

static bool	extra_function(char *tmp, char *pos, char *pos_plus)
{
	if (!valid_key(tmp) || !valid_value(pos))
		return (false);
	if (pos)
		*pos = '=';
	if (pos_plus)
		*(pos_plus) = '+';
	return (true);
}

bool	valid_export_arg(char *tmp)
{
	bool	valid;
	char	*pos;
	char	*pos_plus;

	valid = true;
	if (!ft_isalpha(tmp[0]) && tmp[0] != '_')
		valid = false;
	pos = ft_strchr(tmp, '=');
	if (pos)
		*pos = '\0';
	pos_plus = ft_strchr(tmp, '+');
	if (pos_plus)
	{
		*pos_plus = '\0';
		if (*(pos_plus + 1) == '+')
			valid = false;
	}
	if (!extra_function(tmp, pos, pos_plus))
		valid = false;
	if (!valid)
		error_sh_cmd_msg(1, "export", tmp, \
    "not a valid identifier");
	return (valid);
}
