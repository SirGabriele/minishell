/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:38:33 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:38:34 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_environment_variables(t_env_ms *env_ll, char *outfile,
	t_enum_token outfile_mode, t_pipes_ms *pipes)
{
	int	fd;

	if (outfile_mode == TOK_PIPE)
		fd = pipes->after[1];
	else if (outfile == NULL || outfile_mode == TOK_NULL)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	while (env_ll != NULL)
	{
		if (env_ll->key[0] != '?' && env_ll->value != NULL)
		{
			ft_printf_fd(fd, "%s=%s", env_ll->key, env_ll->value);
			write(fd, "\n", 1);
		}
		env_ll = env_ll->next;
	}
	if (outfile != NULL)
		close(fd);
}

int	ft_env(t_node_ms *node, t_env_ms *env_ll, t_pipes_ms *pipes)
{
	print_environment_variables(env_ll, node->outfile,
		node->outfile_mode, pipes);
	return (0);
}
