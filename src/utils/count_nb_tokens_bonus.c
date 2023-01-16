#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Counts the number of tokens similar to the token_type		*/
/*																*/
/*	Parameters:													*/
/*		tokens	-	a linked list containing all the tokens		*/
/*		token	-	the token_type								*/
/*																*/
/*	Return:														*/
/*		count	-	the count									*/
/*																*/
/****************************************************************/

int	count_nb_tokens(t_token_ms *tokens, t_enum_token token)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		if (tokens->type == token)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
