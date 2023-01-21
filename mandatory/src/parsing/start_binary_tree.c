/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_binary_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:17:44 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/21 00:21:50 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
