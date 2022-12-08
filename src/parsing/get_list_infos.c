#include "../../includes/minishell.h"

static int	is_operator(t_tokens type)
{
	if (type == TOK_AND_OPER || type == TOK_OR_OPER || type == TOK_PIPE)
		return (1);
	return (0);
}

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

static t_token_ms	**split_list(t_token_ms *tokens)
{
	t_token_ms	**splited_tokens;
	t_token_ms	*cpy_tokens;
	int			index_token;

	splited_tokens = malloc(3 * sizeof(t_token_ms *));
	if (!splited_tokens)
		return (NULL);
	splited_tokens[2] = NULL;
	splited_tokens[0] = tokens;
	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->next && is_operator(cpy_tokens->next->type)
			&& check_token_pos(tokens, index_token + 1) == TOK_SHELL)
		{
			splited_tokens[1] = cpy_tokens->next->next;
			cpy_tokens->next = NULL;
			return (splited_tokens);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	free_splited_tokens(splited_tokens);
	return (NULL);
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
		if (!binary_tree->left && !i)
			return (NULL);
		else if (!binary_tree->right && i)
		{
			free_binary_tree(binary_tree->left);
			return (NULL);
		}
		i++;
	}
	return (binary_tree);
}

t_node_ms	*get_list_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;
	t_token_ms	**splited_tokens;

	tokens = del_parenthesis_if_needed(tokens);
	binary_tree = get_node_infos(tokens, shell);
	if (!binary_tree)
		return (NULL);
	splited_tokens = split_list(tokens);
	if (!splited_tokens)
	{
		//free(binary_tree);
		//free_tokens(tokens);
		return (NULL);
	}
	binary_tree = recursive(splited_tokens, binary_tree, shell);
	if (!binary_tree)
	{
		//free_tokens(tokens);
		//free_splited_tokens(splited_tokens);
		return (NULL);
	}
	//free_splited_tokens(splited_tokens);
	return (binary_tree);
}
