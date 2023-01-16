#include "../../includes/minishell.h"

int	check_syntax_par(t_token_ms *tokens, t_env_ms *env_ll)
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
			print_checking_error_msg(")");
			set_exit_code(env_ll, 2);
			return (-1);
		}
		cursor = cursor->next;
	}
	if (pair > 0)
	{
		print_checking_error_msg("(");
		set_exit_code(env_ll, 2);
		return (-1);
	}
	return (0);
}
