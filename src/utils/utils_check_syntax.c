#include "../../includes/minishell.h"

void	print_error_msg(char *msg)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", msg);
}

int	syntax_first_token(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	if (cursor->type == TOK_CL_PAR || cursor->type == TOK_PIPE
		|| cursor->type == TOK_AND_OPER || cursor->type == TOK_OR_OPER)
	{
		print_error_msg(cursor->content);
		set_exit_code(env_ll, 2);
		return (-1);
	}
	else if (cursor->type == TOK_OP_PAR && cursor->next
		&& cursor->next->type == TOK_CL_PAR)
	{
		print_error_msg(cursor->content);
		set_exit_code(env_ll, 2);
		return (-1);
	}
	return (0);
}

int	syntax_and_or(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if ((cursor->type == TOK_AND_OPER || cursor->type == TOK_OR_OPER)
			&& cursor->next && (cursor->next->type == TOK_PIPE
				|| cursor->next->type == TOK_AND_OPER
				|| cursor->next->type == TOK_OR_OPER
				|| cursor->next->type == TOK_CL_PAR))
		{
			print_error_msg(cursor->next->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}

int	syntax_par(t_token_ms *tokens, t_env_ms *env_ll)//a faire
{
	t_token_ms	*cursor;

	cursor = tokens;
	int	pair;

	pair = 0;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_OP_PAR)
			pair++;
		else if (cursor->type == TOK_CL_PAR)
			pair--;
		if (pair < 0)
		{
			print_error_msg(")");
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	if (pair > 0)
	{
		print_error_msg("(");
		set_exit_code(env_ll, 2);
		return (-1);
	}
	return (0);
}

int	syntax_pipe(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_PIPE && cursor->next
			&& (cursor->next->type == TOK_PIPE || cursor->next->type == TOK_CL_PAR
			|| cursor->next->type == TOK_AND_OPER || cursor->next->type == TOK_OR_OPER))
		{
			print_error_msg(cursor->next->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}
