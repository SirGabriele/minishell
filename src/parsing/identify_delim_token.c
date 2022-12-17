#include "../../includes/minishell.h"

static t_enum_token	check_second_half(int index_delimiter, t_enum_token token_type)
{
	if (index_delimiter == 5)
		token_type = TOK_TRUNC;
	else if (index_delimiter == 6)
		token_type = TOK_OR_OPER;
	else if (index_delimiter == 7)
		token_type = TOK_PIPE;
	else if (index_delimiter == 8)
		token_type = TOK_AND_OPER;
	else if (index_delimiter == 9)
		token_type = TOK_NULL;
	return (token_type);
}

static t_enum_token	get_token_type(int index_delimiter, t_enum_token token_type)
{
	if (index_delimiter == 0)
		token_type = TOK_OP_PAR;
	else if (index_delimiter == 1)
		token_type = TOK_CL_PAR;
	else if (index_delimiter == 2)
		token_type = TOK_HEREDOC;
	else if (index_delimiter == 3)
		token_type = TOK_APPEND;
	else if (index_delimiter == 4)
		token_type = TOK_INFILE;
	else
		token_type = check_second_half(index_delimiter, token_type);
	return (token_type);
}

/************************************************************/
/*															*/
/*	Identifies the delimiter								*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	command line						*/
/*		index_delim	-	index of the delimiter				*/
/*															*/
/*	Return:													*/
/*		token_type	-	type of the token					*/
/*															*/
/************************************************************/

t_enum_token	identify_delim_token(int index_delim)
{
	t_enum_token	token_type;

	token_type = TOK_NULL;
	token_type = get_token_type(index_delim, token_type);
	return (token_type);
}
