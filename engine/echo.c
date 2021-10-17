#include "../headers/minishell.h"

static int check_flag(char *str)
{
	int	i;

	i = 0;
		
	if (str && !ft_strncmp("-n", str, 2))
		{
			i += 1;
			while (str[i++] == 'n')
				if (str[i] == '\0')
					return (1);
		}

	return (0);
}

void	ft_echo(t_parse_lst *lst)
{
	bool n_flag; 

	n_flag = false;
	while (lst->args && check_flag(lst->args->arg))
	{
		lst->args = lst->args->next;
		n_flag = true;
	}

	while (lst->args)
	{
		write(1, lst->args->arg, ft_strlen(lst->args->arg));
		if (lst->args->next)
			write(1, " ", 1);
		lst->args = lst->args->next;
	}
	if (!n_flag)
		write(1, "\n", 1);
	write(1, (void *)EOF, 4);
}