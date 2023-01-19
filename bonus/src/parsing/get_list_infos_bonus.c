/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_infos_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:04 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:04 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_node_ms	*recursive(t_token_ms **splitted_tokens, \
	t_node_ms *root, t_enum_token *operators)
{
	root->left = left_branch(splitted_tokens[0],
			root->operator, operators);
	root->right = right_branch(splitted_tokens[1],
			root->operator, operators);
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

	root->operator = identify_splitting_operator(tokens);
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
