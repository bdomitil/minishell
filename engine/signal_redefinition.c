#include "../headers/minishell.h"

void	parent_sign_redif()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	exex_sign_redif()
{
	signal(SIGQUIT, ctrl_slsh);
	signal(SIGINT, ctrl_c_forked);
}

void	hd_sig_redif()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_heredoc);
}