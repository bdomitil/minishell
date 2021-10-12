#include "../headers/minishell.h"

//void	ft_unset(t_parse_lst *lst)
//{
//	t_env	*tmp;
//
//	while (lst->env_lst)
//	{
//		if (!ft_strncmp(lst->args->arg, lst->env_lst->key, ft_strlen(lst->args->arg)))
//			break;
//		tmp = lst->env_lst;
//		lst->env_lst = lst->env_lst->next;
//	}
//	if (!lst->env_lst)
//		return; // error handle
//	if (lst->env_lst->value)
//		free(lst->env_lst->value);
//	if (lst->env_lst->env_type)
//		free (lst->env_lst->env_type);
//	free(lst->env_lst->key);
//	if (lst->env_lst->next)
//		tmp->next = lst->env_lst->next; // does it works?
//	else
//		tmp->next = NULL;
//	free
//}

void	ft_unset(t_parse_lst *lst)
{
	del_env_lst_by_key(lst->env_lst, lst->args->arg);
}