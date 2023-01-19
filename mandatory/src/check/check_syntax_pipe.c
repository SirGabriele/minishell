/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:53:29 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:28:54 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax_pipe(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_PIPE && cursor->next
			&& cursor->next->type == TOK_PIPE)
		{
			print_checking_error_msg(cursor->next->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		else if (cursor->type == TOK_PIPE && !cursor->next)
		{
			print_checking_error_msg(cursor->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}
