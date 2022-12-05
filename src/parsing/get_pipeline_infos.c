#include "../../includes/minishell.h"

static int	tok_is_content(t_token_ms *tokens)
{
	if (tokens->type == TOK_INFILE)
		return (0);
	if (tokens->type == TOK_TRUNC)
		return (0);
	if (tokens->type == TOK_APPEND)
		return (0);
	if (tokens->type == TOK_HEREDOC)
		return (0);
	if (tokens->type == TOK_STRING)
		return (1);
	return (2);
}

static char	*get_pipeline(t_token_ms *tokens)
{
	char		*pipeline;

	pipeline = NULL;
	while (tokens)
	{
		if (tok_is_content(tokens) == 1)
		{
			pipeline = ft_strjoin_free_first(pipeline, tokens->content);
			if (!pipeline)
				return (NULL);
		}
		else if (!tok_is_content(tokens))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (pipeline);
}

t_node_ms	*get_pipeline_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;

	binary_tree = get_redirections_infos(tokens);
	if (!binary_tree)
		return (NULL);
	binary_tree->content = get_pipeline(tokens);
	if (!binary_tree->content)
		return (NULL);
	binary_tree->shell = shell;
	return (binary_tree);
}
