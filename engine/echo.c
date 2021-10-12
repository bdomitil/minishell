#include "../headers/minishell.h"

void	ft_echo(t_parse_lst *lst)
{
	int i; // исправить позже

	i = 0;
	if (!ft_strncmp("-n\0", lst->args->head->arg, 3))
		i = 1;
	if (i && lst->args->next)
		lst->args = lst->args->next;
	while (lst->args)
	{
		write(1, lst->args->arg, ft_strlen(lst->args->arg));
		write(1, " ", 1);
		lst->args = lst->args->next;
	}
	if (!i)
		write(1, "\n", 1);
	write(1, (void *)EOF, 4); // может ломать
}