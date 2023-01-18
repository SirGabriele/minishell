#include "../../includes/minishell_bonus.h"

int	is_operator(t_enum_token type)
{
	if (type == TOK_AND_OPER || type == TOK_OR_OPER || type == TOK_PIPE)
		return (1);
	return (0);
}
