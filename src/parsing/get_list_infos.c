#include "../../includes/minishell.h"

static t_node_ms	*set_node_infos(t_token_ms *tokens, t_enum_token shell)
{
	t_node_ms	*node;

	node = malloc(sizeof(t_node_ms));
	if (node)
	{
		node->first_redir = NULL;
		node->content = NULL;
		node->infile = NULL;
		node->outfile = NULL;
		node->infile_mode = TOK_NULL;
		node->outfile_mode = TOK_NULL;
		node->shell = shell;
		node->operator = identify_splitting_operator(tokens);
	}
	return (node);
}

static t_node_ms	*recursive(t_token_ms **splitted_tokens, \
	t_node_ms *root, t_enum_token shell, t_enum_token *operators)
{
	root->left = left_branch(splitted_tokens[0],
			root->operator, shell, operators);
	root->right = right_branch(splitted_tokens[1],
			root->operator, shell, operators);
	return (root);
}

/****************************************************************/
/*																*/
/*	Gets the list's infos, splits the linked list in two and	*/
/*		launches the recursive									*/
/*																*/
/*	Parameters:													*/
/*		tokens		-	linked list								*/
/*		shell		-	what is command in						*/
/*		operators	- 	array containing the last two 			*/
/*						operators								*/
/*																*/
/*	Return:														*/
/*		root	-	edited node									*/
/*																*/
/****************************************************************/

t_node_ms	*get_list_infos(t_token_ms *tokens, t_enum_token shell, \
	t_enum_token *operators)
{
	t_token_ms	**splitted_tokens;
	t_node_ms	*root;

	root = set_node_infos(tokens, shell);
	if (!root)
		return (NULL);
	splitted_tokens = split_list(tokens);
	if (!splitted_tokens)
	{
		free(root);
		return (NULL);
	}
	root = recursive(splitted_tokens, root, shell, operators);
	if (!root)
	{
		free_splitted_tokens(splitted_tokens);
		return (NULL);
	}
	free(splitted_tokens);
	return (root);
}
