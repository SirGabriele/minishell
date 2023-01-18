/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:05:49 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:05:57 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
