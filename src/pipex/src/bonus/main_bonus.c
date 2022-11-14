/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:29:47 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/06 21:43:50 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if (argc < 5
		|| (argc != 6 && argv[1] != NULL
			&& ft_strncmp(argv[1], "here_doc", 8) == 0))
		return (ft_printf("Usage is <<< ./pipex infile cmd_1 cmd_2"\
		" | ... | cmd_n outfile >>>\n\n\t---Or---\n\n"\
		"<<< ./pipex here_doc LIMITER cmd_1 cmd_2 outfile >>>\n"));
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (-1);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		init_pipex_here_doc(pipex, argc);
	else
		init_pipex(pipex, argc);
	check_args_bonus(pipex, argc, argv, env);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc_requested(pipex, argv, env);
	else
		prepare_bonus(pipex, argc, argv, env);
	clear_program(pipex, NULL);
	return (0);
}
