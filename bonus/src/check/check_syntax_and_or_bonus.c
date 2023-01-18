/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_or_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:53:56 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:03:04 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	check_syntax_and_or(t_token_ms *tokens, t_env_ms *env_ll)
{
	while (tokens != NULL)
	{
		if ((tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER)
			&& tokens->next && (tokens->next->type == TOK_PIPE
				|| tokens->next->type == TOK_AND_OPER
				|| tokens->next->type == TOK_OR_OPER
				|| tokens->next->type == TOK_CL_PAR))
		{
			print_checking_error_msg(tokens->next->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		else if ((tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER)
			&& !tokens->next)
		{
			print_checking_error_msg(tokens->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		tokens = tokens->next;
	}
	return (0);
}
