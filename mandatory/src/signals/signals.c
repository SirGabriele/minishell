/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:42:25 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 23:10:28 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handler_first_readline(int sig)
{
	(void)sig;
	g_signal = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_heredoc(int sig)
{
	(void)sig;
	g_signal = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(0);
}

void	set_signals_first_readline(void)
{
	signal(SIGINT, handler_first_readline);
	signal(SIGQUIT, SIG_IGN);
}
