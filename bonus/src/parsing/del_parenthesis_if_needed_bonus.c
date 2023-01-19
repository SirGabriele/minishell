/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_parenthesis_if_needed_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:50:55 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:50:55 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	check_if_only_redirs_left(t_token_ms *tokens)
{
	while (tokens)
	{
		if (!is_token_type_a_redir(tokens->type))
			return (0);
		else
			tokens = tokens->next->next;
	}
	return (1);
}

/************************************************************/
/*															*/
/*	Checks if command line is between parenthesis			*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list								*/
/*															*/
/*	Return:													*/
/*		0	-	no parenthesis								*/
/*		1	-	parenthesis									*/
/*															*/
/************************************************************/

static t_enum_token	check_parenthesis(t_token_ms *tokens)
{
	int			op_parenthesis;
	int			cl_parenthesis;

	while (tokens && is_token_type_a_redir(tokens->type) && tokens->next
		&& tokens->next->next)
		tokens = tokens->next->next;
	if (tokens && tokens->type == TOK_OP_PAR)
	{
		op_parenthesis = 0;
		cl_parenthesis = 0;
		while (tokens)
		{
			if (tokens->type == TOK_OP_PAR)
				op_parenthesis++;
			else if (tokens->type == TOK_CL_PAR)
				cl_parenthesis++;
			if (op_parenthesis == cl_parenthesis
				&& (!tokens->next || check_if_only_redirs_left(tokens->next)))
				return (TOK_SUBSHELL);
			else if (op_parenthesis == cl_parenthesis && tokens->next)
				return (TOK_SHELL);
			tokens = tokens->next;
		}
	}
	return (TOK_NULL);
}

static t_token_ms	*get_new_tokens_adress(t_token_ms *tokens, int increment)
{
	t_token_ms	*tokens_cpy;

	tokens_cpy = NULL;
	if (increment == 1)
	{	
		tokens_cpy = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tokens_cpy;
	}
	else if (increment == 2)
	{		
		tokens_cpy = tokens->next->next;
		free(tokens->next->content);
		free(tokens->next);
		tokens->next = tokens_cpy;
		while (tokens)
			tokens = tokens->next;
	}
	return (tokens);
}

/************************************************************/
/*															*/
/*	Deletes parenthesis if needed							*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list with potential parenthesis	*/
/*															*/
/*	Return:													*/
/*		tokens	-	linked list without parenthesis			*/
/*															*/
/************************************************************/

t_token_ms	*del_parenthesis_if_needed(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;
	int			op_parenthesis;
	int			cl_parenthesis;

	if (check_parenthesis(tokens) == TOK_SUBSHELL)
	{
		op_parenthesis = 1;
		cl_parenthesis = 0;
		tokens = get_new_tokens_adress(tokens, 1);
		tmp_tokens = tokens;
		while (tmp_tokens)
		{
			if (tmp_tokens->type == TOK_OP_PAR)
				op_parenthesis++;
			else if (tmp_tokens->next && tmp_tokens->next->type == TOK_CL_PAR)
				cl_parenthesis++;
			if (op_parenthesis == cl_parenthesis)
				tmp_tokens = get_new_tokens_adress(tmp_tokens, 2);
			else
				tmp_tokens = tmp_tokens->next;
		}
		tokens = del_parenthesis_if_needed(tokens);
	}
	return (tokens);
}
