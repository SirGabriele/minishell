/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:35:35 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 22:42:29 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	back_slash_n(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}

static void	core_dump(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	set_sigint_sigquit_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_before_fork(void)
{
	signal(SIGINT, back_slash_n);
	signal(SIGQUIT, core_dump);
}
