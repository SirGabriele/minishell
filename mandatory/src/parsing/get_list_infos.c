/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_infos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:31 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/21 00:25:40 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node_ms	*recursive(t_token_ms **splitted_tokens, \
	t_node_ms *root, t_enum_token *operators)
{
	t_enum_token	cpy_operators;

	cpy_operators = operators[1];
	operators[1] = TOK_PIPE;
	root->left = build_binary_tree(splitted_tokens[0], operators);
	if (!root->left)
	{
		free_binary_tree(root);
		return (NULL);
	}
	operators[0] = TOK_PIPE;
	operators[1] = cpy_operators;
	root->right = build_binary_tree(splitted_tokens[1], operators);
	if (!root->right)
	{
		free_binary_tree(root);
		return (NULL);
	}
	return (root);
}

/****************************************************************/
/*																*/
/*	Gets the list's infos, splits the linked list in two and	*/
/*		launches the recursive									*/
/*																*/
/*	Parameters:													*/
/*		tokens		-	linked list								*/
/*		shell		-	what is command in						*/
/*		operators	- 	array containing the last two 			*/
/*						operators								*/
/*																*/
/*	Return:														*/
/*		root	-	edited node									*/
/*																*/
/****************************************************************/

t_node_ms	*get_list_infos(t_node_ms *root, t_token_ms *tokens, \
	t_enum_token *operators)
{
	t_token_ms	**splitted_tokens;

	splitted_tokens = split_list(tokens);
	if (!splitted_tokens)
	{
		free(root);
		return (NULL);
	}
	root = recursive(splitted_tokens, root, operators);
	if (!root)
	{
		free_splitted_tokens(splitted_tokens);
		return (NULL);
	}
	free(splitted_tokens);
	return (root);
}
