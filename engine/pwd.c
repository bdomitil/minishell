#include "../headers/minishell.h"

void	ft_pwd(t_parse_lst *lst)
{
	char *str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		error_sh_cmd_msg(1, "pwd", NULL, strerror(errno));
		return;
	}
	write (1, str, ft_strlen(str)); // 0?
	free (str);
	write(1, "\n", 1);
	write(1, (void *)EOF, 4);
	g_mshl.g_exit_status = 0;
}
