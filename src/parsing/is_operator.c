#include "../../includes/minishell.h"

int	is_operator(t_tokens type)
{
	if (type == TOK_AND_OPER || type == TOK_OR_OPER || type == TOK_PIPE)
		return (1);
	return (0);
}
