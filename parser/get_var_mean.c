/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_mean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:17:16 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 16:40:46 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static char	*join_var(int *i, char *str, char *var, int end_pos)
{
	char	*new_str;

	new_str = NULL;
	if (str[*i + 1] == '?')
		var = ft_itoa(g_mshl.g_exit_status);
	str[*i] = 0;
	new_str = malloc(ft_strlen(var) + \
					ft_strlen(&str[end_pos + *i + 1]) + ft_strlen(str));
	if (!new_str)
		return (NULL);
	ft_memmove(new_str, str, ft_strlen(str));
	ft_memmove(&new_str[*i], var, ft_strlen(var));
	ft_memmove(&new_str[*i + ft_strlen(var)], &str[*i + end_pos + 1], \
										ft_strlen(&str[*i + end_pos]));
	*i += ft_strlen(var);
	free(str);
	free(var);
	return (new_str);
}

char	*get_var_mean(char *str, int *i, t_env *env_lst) // что эт
{
	char	*temp;
	char	*var;
	char	*new_str;
	int		end_pos;

	new_str = NULL;
	end_pos = *i + 1;
	while (ft_isalpha(str[end_pos]) || ft_isalnum(str[end_pos]) \
											|| str[end_pos] == '_')
		end_pos++;
	end_pos = end_pos - *i - 1;
	temp = ft_substr(str, *i + 1, end_pos);
	var = find_env_key(env_lst, temp);
	if (!var && str[*i + 1] != '?')
		ft_memmove(&str[*i], &str[end_pos + *i + 1], \
											ft_strlen(&str[end_pos + *i]));
	else if (var || str[*i + 1] == '?')
		str = join_var(i, str, var, end_pos);
	free(temp);
	return (str);
}
