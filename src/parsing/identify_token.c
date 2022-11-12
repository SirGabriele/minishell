#include "../../includes/minishell.h"

t_tokens	identify_token(int index_delimiter, int length_delimiter)
{
	t_tokens	token_type;

	if (index_delimiter == 2 && length_delimiter == 2)
		token_type = TOK_HEREDOC;
	else if (index_delimiter == 3 && length_delimiter == 2)
		token_type = TOK_OUTF_APPEND;
	else if (index_delimiter == 5 && length_delimiter == 2)
		token_type = TOK_OR_OPER;
	else if (index_delimiter == 0 && length_delimiter == 1)
		token_type = TOK_OP_PAR;
	else if (index_delimiter == 1 && length_delimiter == 1)
		token_type = TOK_CL_PAR;
	else if (index_delimiter == 2 && length_delimiter == 1)
		token_type = TOK_INF_REDIR;
	else if (index_delimiter == 3 && length_delimiter == 1)
		token_type = TOK_OUTF_TRUNC;
	else if (index_delimiter == 4 && length_delimiter == 1)
		token_type = TOK_AND_OPER;
	else if (index_delimiter == 5 && length_delimiter == 1)
		token_type = TOK_PIPE;
	return (token_type);
}
