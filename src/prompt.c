/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:32:20 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/05 11:06:41 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_user_input(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

void	ft_signal(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	cmd_prompt(char **env)
{
	char	*user_input;
	(void)env;
	while (1)
	{
		user_input = readline("minishell> ");
		if (!user_input)
		{
			rl_clear_history();
			write(1, "exit\n", 4);
			return (0);
		}
		if (ft_strncmp(user_input, "exit", 4) == 0)
		{
			rl_clear_history();
			free_user_input(user_input);
			return (0);
		}
		if (ft_strlen(user_input) > 0)
			add_history(user_input);
		if (launch_program(user_input) == -1)
		{
			free_user_input(user_input);
			return (-1);
		}
		else
		{
			ft_printf("%s\n", user_input);
			free_user_input(user_input);
		}
	}
	return (0);
}
