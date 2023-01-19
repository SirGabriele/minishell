/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:46 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:12:47 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	g_signal_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_env_ms	*env_ll;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("This program does not take any parameter\n", 2);
		return (1);
	}
	env_ll = convert_env_arr_into_ll((const char **)env);
	cmd_prompt(env_ll);
	free_env_list(env_ll);
	return (0);
}
