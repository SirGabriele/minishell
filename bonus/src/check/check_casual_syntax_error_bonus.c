#include "../../includes/minishell_bonus.h"

static int    check_par_only(t_token_ms *tokens, t_env_ms *env_ll)
{
    t_token_ms    *cursor;

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
        if ((cursor->type == TOK_STRING || cursor->type == TOK_CL_PAR)
                        && cursor->next && cursor->next->type == TOK_OP_PAR)
                {
                        print_checking_error_msg(cursor->next->content);
                        free_tokens(tokens);
                        set_exit_code(env_ll, 2);
                        return (-1);
                }
/*                if (cursor->type == TOK_CL_PAR && cursor->next
					&& cursor->next->type != TOK_PIPE
					&& cursor->next->type != TOK_AND_OPER
					&& cursor->next->type != TOK_OR_OPER)
                {
                        print_checking_error_msg(cursor->next->content);
                        free_tokens(tokens);
                        set_exit_code(env_ll, 2);
                        return (-1);
                }*/
        cursor = cursor->next;
    }
    return (0);
}


/************************************************************/
/*															*/
/*	Checks the main syntax error							*/
/*															*/
/*															*/
/*															*/
/*	Parameters:												*/
/*		x - def												*/
/*		x - def												*/
/*															*/
/*	Return:													*/
/*		x - def												*/
/*		x - def												*/
/*															*/
/************************************************************/

int	check_casual_syntax_error(char **user_input, t_env_ms *env_ll)
{
	t_token_ms	*cursor;
	t_token_ms	*tokens;

	tokens = lexer(*user_input);
	if (check_par_only(tokens, env_ll) == -1)
		return (-1);
	cursor = tokens;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_TRUNC || cursor->type == TOK_APPEND
			|| cursor->type == TOK_INFILE || cursor->type == TOK_HEREDOC)
//			|| cursor->type == TOK_OP_PAR
//			|| (cursor->type == TOK_CL_PAR && cursor == tokens))
		{
/*			if (cursor->type == TOK_OP_PAR && cursor->next && cursor->next->type == TOK_CL_PAR)
			{
				ft_printf_fd(2, "minishell: syntax error near unexpected token `)'\n",
					cursor->next->content);
				set_exit_code(env_ll, 2);
				return (-1);
			}*/
			if (!cursor->next/* && cursor->type != TOK_CL_PAR*/)
			{
				print_checking_error_msg("newline");
				free_tokens(tokens);
				set_exit_code(env_ll, 2);
				return (-1);
			}
			else if (cursor->next && cursor->next->type != TOK_STRING)
/*				|| (cursor->type == TOK_OP_PAR && cursor->next->type == TOK_CL_PAR)
				|| (cursor->type == TOK_CL_PAR && cursor->next->type == TOK_OP_PAR))*/
			{
				print_checking_error_msg(cursor->next->content);
				free_tokens(tokens);
				set_exit_code(env_ll, 2);
				return (-1);
			}
		}
		cursor = cursor->next;
	}
	free_tokens(tokens);
	return (0);
}
