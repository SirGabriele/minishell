#include "../../includes/minishell.h"

static t_node_ms	*initialize_everything(void)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	binary_tree->left = NULL;
	binary_tree->right = NULL;
	binary_tree->content = NULL;
	binary_tree->first_redir = NULL;
	binary_tree->infile = NULL;
	binary_tree->outfile = NULL;
	binary_tree->infile_mode = TOK_NULL;
	binary_tree->outfile_mode = TOK_NULL;
	binary_tree->shell = TOK_NULL;
	binary_tree->operator = TOK_NULL;
	return (binary_tree);
}

static int	tok_is_content(t_token_ms *tokens)
{
	if (tokens->type == TOK_INFILE)
		return (1);
	if (tokens->type == TOK_TRUNC)
		return (1);
	if (tokens->type == TOK_APPEND)
		return (1);
	if (tokens->type == TOK_HEREDOC)
		return (1);
	return (0);
}

static int	nb_redirs(t_token_ms *tokens)
{
	while (tokens)
	{
		if (tok_is_content(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

static char	**get_pipeline(t_token_ms *tokens)
{
	char		**pipelines;
	int			nb_tokens_left;
	int			i;

	nb_tokens_left = count_nb_of_tokens_left(tokens);
	pipelines = malloc((nb_tokens_left + 1) * sizeof(char *));
	if (!pipelines)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == TOK_STRING)
		{
			pipelines[i] = NULL;
			pipelines[i] = ft_strjoin(pipelines[i], tokens->content);
			if (!pipelines[i])
				return (NULL);
		}
		i++;
		tokens = tokens->next;
	}
	return (pipelines);
}

t_node_ms	*get_pipeline_infos(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;

	binary_tree = initialize_everything();
	if (!binary_tree)
		return (NULL);
	if (nb_redirs(tokens))
	{
		binary_tree = get_redirections_infos(tokens, binary_tree);
		if (!binary_tree)
			return (NULL);
	}
	binary_tree->content = get_pipeline(tokens);
	if (!binary_tree->content)
	{
		//free_redirs_list(binary_tree->first_redir);
		//free_redirs_infos(binary_tree);
		//free(binary_tree);
		return (NULL);
	}
	binary_tree->shell = shell;
	return (binary_tree);
}
