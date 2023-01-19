/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:36:31 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:36:35 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_status;

int	main(int argc, char **argv, char **env)
{
	t_env_ms	*env_ll;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("This program does not take any parameter\n", 2);
		return (1);
	}
	env_ll = convert_env_arr_into_ll((const char **)env);
	signal(SIGINT, handler_first_readline);
	signal(SIGQUIT, SIG_IGN);
	cmd_prompt(env_ll);
	free_env_list(env_ll);
	return (0);
}
