/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_binary_tree_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:42 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:42 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_enum_token	*initialize_operators(void)
{
	t_enum_token	*operators;

	operators = malloc(2 * sizeof(t_enum_token));
	if (!operators)
	{
		perror(NULL);
		return (NULL);
	}
	operators[0] = TOK_NULL;
	operators[1] = TOK_NULL;
	return (operators);
}

/************************************************************/
/*															*/
/*	Creates binary_tree										*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list of tokens					*/
/*															*/
/*	Return:													*/
/*		root	-	root of binary_tree						*/
/*															*/
/************************************************************/

t_node_ms	*start_binary_tree(t_token_ms *tokens)
{
	t_node_ms		*root;
	t_enum_token	*operators;

	operators = initialize_operators();
	if (!operators)
		return (NULL);
	root = build_binary_tree(tokens, operators);
	free(operators);
	return (root);
}
