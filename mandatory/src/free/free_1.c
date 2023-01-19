/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:40:29 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:40:30 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;

	while (tokens)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens_cpy = tokens->next;
		free(tokens);
		tokens = tokens_cpy;
	}
}

void	free_splitted_tokens(t_token_ms **splitted_tokens)
{
	free_tokens(splitted_tokens[0]);
	free_tokens(splitted_tokens[1]);
	free(splitted_tokens);
}

void	free_redirs_list(t_redir_ms *first_redir)
{
	t_redir_ms	*tmp_first_redir;

	while (first_redir)
	{
		free(first_redir->file_name);
		first_redir->file_name = NULL;
		tmp_first_redir = first_redir->next;
		free(first_redir);
		first_redir = tmp_first_redir;
	}
}

void	free_redirs_infos(t_node_ms *binary_tree)
{
	free(binary_tree->infile);
	free(binary_tree->outfile);
	binary_tree->infile = NULL;
	binary_tree->outfile = NULL;
}
