/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:32:20 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/04 11:13:25 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int sig)
{
	(void)sig;
	ft_printf("\nminishell> ");
	rl_redisplay();
}

void	cmd_prompt(void)
{
	char	*line_read;

	while (1)
	{
		line_read = readline("minishell> ");
		if (line_read)
			add_history(line_read);
		line_read = get_cmd_parsed(line_read);
		ft_printf("%s\n", line_read);
	}
}
