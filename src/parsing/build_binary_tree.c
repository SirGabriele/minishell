#include "../../includes/minishell.h"

static t_token_ms	*del_redirs_tokens(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;
	t_token_ms	*cpy_tokens;

	tmp_tokens = tokens;
	while (tokens)
	{
		if (tokens->next && is_token_type_a_redir(tokens->next->type))
		{
			cpy_tokens = tokens->next->next->next;
			free(tokens->next->next->content);
			free(tokens->next->next);
			free(tokens->next->content);
			free(tokens->next);
			tokens->next = cpy_tokens;
		}
		tokens = tokens->next;
	}
	return (tmp_tokens);
}

static t_node_ms	*set_node_infos(void)
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
		node->shell = TOK_NULL;
		node->operator = TOK_NULL;
	}
	return (node);
}

static t_node_ms	*node_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token *operators)
{
	root = set_node_infos();
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = get_redirections_infos(root, tokens, operators);
	if (!root)
		return (NULL);
	tokens = del_redirs_tokens(tokens);
	root->shell = check_parenthesis(tokens);
	tokens = del_parenthesis_if_needed(tokens);
	root = get_list_infos(root, tokens, operators);
	free_tokens(tokens);
	return (root);
}

static t_node_ms	*pipeline_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token *operators)
{
	root = ft_lstnew_node(tokens);
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	tokens = del_parenthesis_if_needed(tokens);
	root = get_pipeline_infos(root, tokens, operators);
	free_tokens(tokens);
	return (root);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token *operators)
{
	t_node_ms		*root;
	t_enum_token	oper_pos;

	root = NULL;
	oper_pos = what_is_oper_in(tokens);
	if (oper_pos)
		root = node_related(tokens, root, operators);
	else
		root = pipeline_related(tokens, root, operators);
	return (root);
}
