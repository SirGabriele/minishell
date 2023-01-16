#include "../../includes/minishell.h"

int	check_syntax_pipe(t_token_ms *tokens, t_env_ms *env_ll)
{
	t_token_ms	*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_PIPE && cursor->next
			&& (cursor->next->type == TOK_PIPE || cursor->next->type == TOK_CL_PAR
			|| cursor->next->type == TOK_AND_OPER || cursor->next->type == TOK_OR_OPER))
		{
			print_checking_error_msg(cursor->next->content);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}
