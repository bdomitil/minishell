#include "../headers/minishell.h"

void	ft_pwd(t_parse_lst *lst)
{
	char *str;

	str = find_env_key(lst->env_lst, "PWD");
	write (1, str, ft_strlen(str)); // 0?
	free (str);
	write(1, "\n", 1);
	write(1, (void *)EOF, 4);
}
