#include "../../includes/minishell.h"

static t_node_ms	*lstnew_node(void)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	binary_tree->left = NULL;
	binary_tree->right = NULL;
	binary_tree->content = NULL;
	binary_tree->first_redir = NULL;
	binary_tree->infile = NULL;
	binary_tree->outfile = NULL;
	binary_tree->infile_mode = TOK_NULL;
	binary_tree->outfile_mode = TOK_NULL;
	binary_tree->shell = TOK_NULL;
	binary_tree->operator = TOK_NULL;
	return (binary_tree);
}

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

/************************************************************/
/*															*/
/*	Gets redirections and stock them in a list. Gets mode 	*/
/*	and file of th last infile/outfile redirection			*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	link								*/
/*		operators	-	the last two operators of the		*/
/*						command line						*/
/*															*/
/*	Return:													*/
/*		binary_tree	-	edited binary tree					*/
/*															*/
/************************************************************/

t_node_ms	*get_redirections_infos(t_token_ms *tokens, t_enum_token *operators)
{
	t_node_ms	*binary_tree;

	binary_tree = lstnew_node();
	if (!binary_tree)
		return (NULL);
	if (nb_redirs(tokens))
	{
		binary_tree->first_redir = get_redirections_list(tokens);
		if (!binary_tree->first_redir)
			return (NULL);
		binary_tree = manage_modes_and_files(binary_tree);
		if (!binary_tree)
			return (NULL);
	}
	if (!binary_tree->infile_mode)
		binary_tree->infile_mode = operators[0];
	if (!binary_tree->outfile_mode)
		binary_tree->outfile_mode = operators[1];
	return (binary_tree);
}
