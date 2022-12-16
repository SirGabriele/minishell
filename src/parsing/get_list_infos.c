#include "../../includes/minishell.h"

static t_node_ms	*set_node_infos(t_token_ms *tokens, t_enum_token shell)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (binary_tree)
	{
		binary_tree->first_redir = NULL;
		binary_tree->content = NULL;
		binary_tree->infile = NULL;
		binary_tree->outfile = NULL;
		binary_tree->infile_mode = TOK_NULL;
		binary_tree->outfile_mode = TOK_NULL;
		binary_tree->shell = shell;
		binary_tree->operator = identify_splitting_operator(tokens);
	}
	return (binary_tree);
}

static t_node_ms	*recursive(t_token_ms **splited_tokens, \
	t_node_ms *binary_tree, t_enum_token shell, t_enum_token *operators)
{
	binary_tree->left = left_branch(splited_tokens[0],
			binary_tree->operator, shell, operators);
	binary_tree->right = right_branch(splited_tokens[1],
			binary_tree->operator, shell, operators);
	return (binary_tree);
}

/************************************************************/
/*															*/
/*	Gets the list's infos, split the linked list in two and	*/
/*	launch the recursive									*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	linked list							*/
/*		shell		-	what is command in					*/
/*		operators	- 	array containing the last two 		*/
/*						operators							*/
/*															*/
/*	Return:													*/
/*		binary_tree	-	edited binary_tree					*/
/*															*/
/************************************************************/

t_node_ms	*get_list_infos(t_token_ms *tokens, t_enum_token shell, \
	t_enum_token *operators)
{
	t_node_ms	*binary_tree;
	t_token_ms	**splited_tokens;

	binary_tree = set_node_infos(tokens, shell);
	if (!binary_tree)
		return (NULL);
	splited_tokens = split_list(tokens);
	if (!splited_tokens)
	{
		free(binary_tree);
		return (NULL);
	}
	binary_tree = recursive(splited_tokens, binary_tree, shell, operators);
	if (!binary_tree)
	{
		free_splited_tokens(splited_tokens);
		return (NULL);
	}
	free(splited_tokens);
	return (binary_tree);
}
