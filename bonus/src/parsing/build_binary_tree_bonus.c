/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_binary_tree_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:50:52 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:50:52 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
		node->shell = TOK_NULL;
		node->operator = TOK_NULL;
	}
	return (node);
}

static t_node_ms	*node_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token *operators)
{
	root = set_node_infos();
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	tokens = del_parenthesis_if_needed(tokens);
	root = get_list_infos(root, tokens, operators);
	free_tokens(tokens);
	return (root);
}

static t_node_ms	*pipeline_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token *operators)
{
	root = ft_lstnew_node(operators);
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	tokens = del_parenthesis_if_needed(tokens);
	root = get_pipeline_infos(root, tokens, operators);
	free_tokens(tokens);
	return (root);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token *operators)
{
	t_node_ms		*root;
	t_enum_token	oper_pos;

	root = NULL;
	oper_pos = what_is_oper_in(tokens);
	if (oper_pos)
		root = node_related(tokens, root, operators);
	else
		root = pipeline_related(tokens, root, operators);
	return (root);
}
