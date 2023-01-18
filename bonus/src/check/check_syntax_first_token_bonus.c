/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_first_token_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:53:37 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 12:53:38 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	check_syntax_first_token(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	if (cursor->type == TOK_CL_PAR || cursor->type == TOK_PIPE
		|| cursor->type == TOK_AND_OPER || cursor->type == TOK_OR_OPER)
	{
		print_checking_error_msg(cursor->content);
		set_exit_code(env_ll, 2);
		return (-1);
	}
	else if (cursor->type == TOK_OP_PAR && cursor->next
		&& cursor->next->type == TOK_CL_PAR)
	{
		print_checking_error_msg(cursor->content);
		set_exit_code(env_ll, 2);
		return (-1);
	}
	return (0);
}
