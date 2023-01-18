/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:05:18 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:05:18 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
