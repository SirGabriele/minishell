/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_requested.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:56:46 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:02:19 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	read_loop(int std_in_copy, char **argv, int *pipehd)
{
	char	*user_input;
	int		length_limiter;

	length_limiter = ft_strlen(argv[2]);
	while (1)
	{
		ft_printf("heredoc> ");
		user_input = get_next_line(std_in_copy);
		if (ft_strncmp(user_input, argv[2], length_limiter) == 0
			&& user_input[length_limiter + 1] == '\0')
		{
			close(std_in_copy);
			free(user_input);
			user_input = get_next_line(std_in_copy);
			close(pipehd[1]);
			break ;
		}
		ft_putstr_fd(user_input, pipehd[1]);
		free(user_input);
		user_input = NULL;
	}
}

void	here_doc_requested(t_pipex *pipex, char **argv, char **env)
{
	int		pipehd[2];
	int		std_in_copy;

	if (pipe(pipehd) == -1)
		clear_program(pipex, "In HDR.c, malloc failed");
	std_in_copy = dup(STD_IN);
	read_loop(std_in_copy, argv, pipehd);
	two_commands_requested(pipex, argv, env, pipehd);
	close(pipehd[0]);
}
