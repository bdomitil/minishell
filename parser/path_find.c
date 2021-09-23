/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 02:45:17 by bdomitil          #+#    #+#             */
/*   Updated: 2021/09/23 00:49:25 by bdomitil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parse.h"

static int check_file_exist(char *file)
{
	struct stat stat_st = {0};
	int         res;

	res = stat(file, &stat_st) + 1;
	free(file);
	return (res);
}

static void free_and_exit(char **str, char **splited_pathes, \
													char **file, char **path)
{
	if (!(*splited_pathes))
	{
		// free(splited_pathes);
		free(*path);
		free(*file);
		return ;
	}
	else
	{
		free(*str);
		*str = ft_strjoin(*splited_pathes, *file);
		free(*path);
		while (*splited_pathes)
		{
			free(*splited_pathes);
			splited_pathes++;
		}
		// free(splited_pathes);
		free(*file);   
	}    
}

void    join_path(char **str, t_env *env_lst)
{
	char	*file;
	char	**splited_pathes;
	char	*path;
	char	**split_start;

	file = ft_strjoin("/", *str);
	path = find_env_key(env_lst, "PATH");
	splited_pathes = split_out_quotes(path, ':');
	split_start = splited_pathes;
	while (*splited_pathes)
	{
		if (check_file_exist(ft_strjoin(*splited_pathes, file)))
			break;
		free(*splited_pathes);
		splited_pathes++;
	}
	free_and_exit(str, splited_pathes, &file, &path);
	free(split_start);
}