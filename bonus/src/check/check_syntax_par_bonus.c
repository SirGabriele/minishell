/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_par_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:52:55 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 12:52:56 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	check_par_only(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_OP_PAR && cursor->next
			&& (cursor->next->type == TOK_CL_PAR))
		{
			print_checking_error_msg("(");
			free_tokens(tokens);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		else if ((cursor->type == TOK_STRING || cursor->type == TOK_CL_PAR)
			&& cursor->next && cursor->next->type == TOK_OP_PAR)
		{
			print_checking_error_msg(cursor->next->content);
			free_tokens(tokens);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}

static int	count_nb_token(t_token_ms *tokens, t_enum_token type)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		if (tokens->type == type)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	check_syntax_par(t_token_ms *tokens, t_env_ms *env_ll)
{
	int	nb_op_par;
	int	nb_cl_par;
	int	difference;

	nb_op_par = count_nb_token(tokens, TOK_OP_PAR);
	nb_cl_par = count_nb_token(tokens, TOK_CL_PAR);
	difference = nb_op_par - nb_cl_par;
	if (difference > 0)
		print_checking_error_msg("(");
	else if (difference < 0)
		print_checking_error_msg(")");
	else if (check_par_only(tokens, env_ll) == -1)
		;
	else
		return (0);
	set_exit_code(env_ll, 2);
	return (-1);
}
