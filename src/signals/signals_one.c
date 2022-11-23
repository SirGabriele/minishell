#include "../../includes/minishell.h"

void	ft_signal_user_input(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_heredoc(int sig)
{
	(void)sig;
	close(0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
