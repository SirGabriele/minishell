/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_oper_in_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:09 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:07:30 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_enum_token	what_is_oper_in(t_token_ms *tokens)
{
	t_enum_token	oper_pos;
	t_token_ms		*cpy_tokens;
	int				index_token;

	oper_pos = TOK_NULL;
	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->type == TOK_AND_OPER || cpy_tokens->type == TOK_OR_OPER
			|| cpy_tokens->type == TOK_PIPE)
		{
			if (is_token_in_parenthesis(tokens, index_token) == TOK_SHELL)
				return (TOK_SHELL);
			else if (is_token_in_parenthesis(tokens, index_token)
				== TOK_SUBSHELL)
				oper_pos = TOK_SUBSHELL;
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (oper_pos);
}
