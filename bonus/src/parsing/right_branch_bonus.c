/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_branch_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:34 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:35 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_enum_token	*cpy_operators(t_enum_token *operators)
{
	t_enum_token	*operators_tmp;

	operators_tmp = malloc(2 * sizeof(t_enum_token));
	if (!operators_tmp)
		return (NULL);
	operators_tmp[0] = operators[0];
	operators_tmp[1] = operators[1];
	return (operators_tmp);
}

/*******************************************/
/*   right_branch :                        */
/*                                         */
/*   Launch the recursive for the          */
/*   right branch                          */
/*                                         */
/*   operators[0] represents the infile    */
/*   of the command                        */
/*   operators[1] represents the outfile   */
/*   of the command                        */
/*******************************************/

t_node_ms	*right_branch(t_token_ms *tokens, t_enum_token oper, \
	t_enum_token *operators)
{
	t_node_ms		*binary_tree;
	t_enum_token	*operators_tmp;

	operators_tmp = cpy_operators(operators);
	if (!operators_tmp)
		return (NULL);
	if (oper == TOK_PIPE)
		operators_tmp[0] = oper;
	else
		operators_tmp[0] = TOK_NULL;
	binary_tree = build_binary_tree(tokens, operators_tmp);
	free(operators_tmp);
	return (binary_tree);
}
