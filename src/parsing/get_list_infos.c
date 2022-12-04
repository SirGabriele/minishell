#include "../../includes/minishell.h"

/*static char	*get_pipeline_2(t_token_ms *tokens) //a supprimer, ici juste pour un test
{
	char		*pipeline;

	pipeline = NULL;
	while (tokens)
	{
		pipeline = ft_strjoin_free_first(pipeline, tokens->content);
		if (!pipeline)
			return (NULL);
		tokens = tokens->next;
	}
	return (pipeline);
}*/

static t_node_ms	*get_node(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (binary_tree)
	{
		binary_tree->first_redir = NULL;
		//binary_tree->content = get_pipeline_2(tokens);//a modifier : mettre content a NULL;
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
		if (cpy_tokens->next && (cpy_tokens->next->type == TOK_AND_OPER
				|| cpy_tokens->next->type == TOK_OR_OPER
				|| cpy_tokens->next->type == TOK_PIPE)
			&& check_token_pos(tokens, index_token + 1) == TOK_SHELL)
		{
			splited_tokens[1] = cpy_tokens->next->next;
			cpy_tokens->next = NULL;
			return (splited_tokens);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
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
		if (!binary_tree->left && !binary_tree->right)
			return (NULL);
		i++;
	}
	return (binary_tree);
}

t_node_ms	*get_list_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;
	t_token_ms	**splited_tokens;

	tokens = supp_parenthesis_if_needed(tokens);
	binary_tree = get_node(tokens, shell);
	if (!binary_tree)
		return (NULL);
	splited_tokens = split_list(tokens);
	if (!splited_tokens)
		return (NULL);
	binary_tree = recursive(splited_tokens, binary_tree, shell);
	if (!binary_tree)
		return (NULL);
	//free_tokens(splited_tokens[0]);
	//free_tokens(splited_tokens[1]);
	//free(splited_tokens);
	return (binary_tree);
}
