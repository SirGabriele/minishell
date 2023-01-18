#include "../../includes/minishell.h"

static t_node_ms	*recursive(t_token_ms **splitted_tokens, \
	t_node_ms *root, t_enum_token shell)
{
	root->left = build_binary_tree(splitted_tokens[0], shell);
	if (!root->left)
	{
		free_binary_tree(root);
		return (NULL);
	}
	root->right = build_binary_tree(splitted_tokens[1], shell);
	if (!root->right)
	{
		free_binary_tree(root);
		return (NULL);
	}
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

t_node_ms	*get_list_infos(t_node_ms *root, t_token_ms *tokens, \
	t_enum_token shell)
{
	t_token_ms	**splitted_tokens;

	splitted_tokens = split_list(tokens);
	if (!splitted_tokens)
	{
		free(root);
		return (NULL);
	}
	root = recursive(splitted_tokens, root, shell);
	if (!root)
	{
		free_splitted_tokens(splitted_tokens);
		return (NULL);
	}
	free(splitted_tokens);
	return (root);
}
