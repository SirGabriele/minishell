/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_in_parenthesis_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:06:51 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:06:51 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_enum_token	is_token_in_parenthesis(t_token_ms *tokens, int token_pos)
{
	int	op_parenthesis;
	int	cl_parenthesis;
	int	index_token;

	op_parenthesis = 0;
	cl_parenthesis = 0;
	index_token = 1;
	while (tokens)
	{
		if (index_token == token_pos && op_parenthesis > cl_parenthesis)
			return (TOK_SUBSHELL);
		else if (index_token == token_pos && op_parenthesis == cl_parenthesis)
			return (TOK_SHELL);
		else if (tokens->type == TOK_OP_PAR)
			op_parenthesis++;
		else if (tokens->type == TOK_CL_PAR)
			cl_parenthesis++;
		index_token++;
		tokens = tokens->next;
	}
	return (TOK_NULL);
}
