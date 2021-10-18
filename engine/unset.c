#include "../headers/minishell.h"

void	ft_unset(t_parse_lst *lst)
{
	while (lst->args)
	{
		del_env_lst_by_key(lst->env_lst, lst->args->arg); // сюда ошибку выхода
		lst->args = lst->args->next;
	}
}