/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_binary_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:20 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/20 01:47:09 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node_ms	*set_node_infos(void)
{
	t_node_ms	*node;

	node = malloc(sizeof(t_node_ms));
	if (node)
	{
		node->first_redir = NULL;
		node->content = NULL;
		node->infile = NULL;
		node->outfile = NULL;
		node->infile_mode = TOK_NULL;
		node->outfile_mode = TOK_NULL;
		node->operator = TOK_PIPE;
		node->shell = TOK_NULL;
	}
	return (node);
}

static t_node_ms	*node_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token shell)
{
	root = set_node_infos();
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = get_list_infos(root, tokens, shell);
	free_tokens(tokens);
	return (root);
}

static t_node_ms	*pipeline_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token shell)
{
	root = ft_lstnew_node(shell);
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = get_pipeline_infos(root, tokens);
	free_tokens(tokens);
	return (root);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token shell)
{
	t_node_ms		*root;

	root = NULL;
	if (is_there_pipes(tokens))
		root = node_related(tokens, root, shell);
	else
		root = pipeline_related(tokens, root, shell);
	return (root);
}

t_node_ms	*start_binary_tree(t_token_ms *tokens)
{
	t_node_ms		*root;
	t_enum_token	shell;

	shell = TOK_SHELL;
	if (is_there_pipes(tokens))
		shell = TOK_SUBSHELL;
	root = build_binary_tree(tokens, shell);
	return (root);
}
