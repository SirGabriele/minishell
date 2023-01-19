/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:18 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:19 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_memory_fork_and_exit(t_pipes_ms *pipes, char **env_arr,
	t_env_ms *env_ll, int exit_code)
{
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	free_double_arr(env_arr);
	free(pipes);
	close(0);
	close(1);
	close(2);
	exit(exit_code);
}

void	print_content_pipe(t_pipes_ms *pipes, t_env_ms *env_ll)
{
	char	**env_arr;
	char	**content;
	char	*cat_path;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		dup2(pipes->after[0], 0);
		close(pipes->after[0]);
		close(pipes->after[1]);
		content = malloc(sizeof(char *) * 2);
		content[0] = ft_strdup("cat");
		content[1] = NULL;
		env_arr = convert_env_ll_into_arr(env_ll);
		cat_path = verify_cmd_path("cat", env_arr);
		execve(cat_path, content, env_arr);
		free_double_arr(content);
		free(cat_path);
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 1);
	}
}
