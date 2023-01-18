#include "../../includes/minishell_bonus.h"

void	handler_first_readline(int sig)
{
	(void)sig;

	g_signal_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_sigint_sigquit(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_sigint_sigquit(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_heredoc(int sig)
{
	(void)sig;

	g_signal_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(0);
}
