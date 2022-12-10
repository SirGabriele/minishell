#include "../../includes/minishell.h"

static t_node_ms	*get_node_infos(t_token_ms *tokens, t_tokens shell)
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
		binary_tree->operator = identify_operator(tokens);
	}
	return (binary_tree);
}

static t_node_ms	*recursive(t_token_ms **splited_tokens, t_node_ms *binary_tree, t_tokens shell)
{
	t_tokens	shell_tmp;
	int			i;

	i = 0;
	while (i < 2)
	{
		shell_tmp = shell;
		if (shell == TOK_SHELL)
		{
			if (check_parenthesis(splited_tokens[i]) == TOK_SUBSHELL)
				shell_tmp = TOK_SUBSHELL;
		}
		if (i == 0)
			binary_tree->left = build_binary_tree(splited_tokens[i], shell_tmp);
		else if (i == 1)
			binary_tree->right = build_binary_tree(splited_tokens[i], shell_tmp);
		i++;
	}
	return (binary_tree);
}

t_node_ms	*get_list_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;
	t_token_ms	**splited_tokens;

	binary_tree = get_node_infos(tokens, shell);
	if (!binary_tree)
		return (NULL);
	splited_tokens = split_list(tokens);
	if (!splited_tokens)
	{
		free(binary_tree);
		return (NULL);
	}
	binary_tree = recursive(splited_tokens, binary_tree, shell);
	if (!binary_tree)
	{
		free_splited_tokens(splited_tokens);
		return (NULL);
	}
	free(splited_tokens);
	return (binary_tree);
}
