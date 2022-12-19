#include "../../includes/minishell.h"

static int	tok_is_content(t_token_ms *tokens)
{
	if (tokens->type == TOK_INFILE)
		return (1);
	if (tokens->type == TOK_TRUNC)
		return (1);
	if (tokens->type == TOK_APPEND)
		return (1);
	if (tokens->type == TOK_HEREDOC)
		return (1);
	return (0);
}

static int	nb_redirs(t_token_ms *tokens)
{
	while (tokens)
	{
		if (tok_is_content(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/****************************************************************/
/*																*/
/*	Gets redirections and stocks them in a list. Gets mode		*/
/*	and file_name of the last infile and outfile redirection	*/
/*																*/
/*	Parameters:													*/
/*		tokens		-	link									*/
/*		operators	-	the last two operators of the			*/
/*						command line							*/
/*																*/
/*	Return:														*/
/*		root	-	edited binary tree							*/
/*																*/
/****************************************************************/

t_node_ms	*get_redirections_infos(t_node_ms *root, t_token_ms *tokens, \
	t_enum_token *operators)
{
	if (nb_redirs(tokens))
	{
		root->first_redir = get_redirections_list(tokens);
		if (!root->first_redir)
			return (NULL);
		root = manage_modes_and_files(root);
		if (!root)
			return (NULL);
	}
	if (!root->infile_mode)
		root->infile_mode = operators[0];
	if (!root->outfile_mode)
		root->outfile_mode = operators[1];
	return (root);
}
