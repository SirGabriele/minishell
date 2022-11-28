#include "../../includes/minishell.h"

static char	*get_pipeline(t_token_ms *tokens)
{
	char		*pipeline;

	pipeline = NULL;
	while (tokens)
	{
		if (tokens->type != TOK_OP_PAR && tokens->type != TOK_CL_PAR)
		{
			pipeline = ft_strjoin_free_first(pipeline, tokens->content);
			if (!pipeline)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (pipeline);
}

t_node_ms	*get_pipeline_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	/*binary_tree = get_redirections_infos(tokens);
	if (!binary->content)
		return (NULL);*/
	binary_tree->content = get_pipeline(tokens);
	if (!binary_tree->content)
		return (NULL);
	binary_tree->shell = shell;
	return (binary_tree);
}
