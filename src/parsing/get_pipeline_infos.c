#include "../../includes/minishell.h"

static char	*get_pipeline(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;
	char		*pipeline;

	pipeline = ft_strjoin(pipeline, tokens->content);
	if (!pipeline)
		return (NULL);
	tokens = tokens->next;
	while (tokens->next)
	{
		pipeline = ft_strjoin_free_first(pipeline, tokens->content);
		if (!pipeline)
			return (NULL);
		tokens = tokens->next;
	}
	pipeline =
	return (pipeline);
}

t_node_ms	*get_pipeline_infos(t_token_ms *tokens)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	/*binary_tree = get_redirections_infos(tokens);
	if (!binary->content)
		return (NULL);*/
	binary_tree->content = get_pipeline(tokens);
	if (!binary->content)
		return (NULL);
	return (binary_tree);
}
