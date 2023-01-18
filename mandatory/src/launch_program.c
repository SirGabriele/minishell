#include "../includes/minishell.h"

static t_token_ms	*get_tokens_parsed(char *user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens_parsed;
	t_token_ms	*tokens_unparsed;

	tokens_unparsed = lexer(user_input);
	if (!tokens_unparsed)
		return (NULL);
	tokens_parsed = lexer(user_input);
	if (tokens_parsed)
		tokens_parsed = parse_quotes(tokens_parsed);
	if (tokens_parsed)
		tokens_parsed = expand_var_with_dollar(tokens_unparsed, tokens_parsed, \
			env_ll);
	free_tokens(tokens_unparsed);
	return (tokens_parsed);
}

static t_node_ms	*parsing(char *user_input, t_env_ms *env_ll)
{
	t_token_ms		*tokens_parsed;
	t_enum_token	shell;
	t_node_ms		*root;

	tokens_parsed = get_tokens_parsed(user_input, env_ll);
	if (!tokens_parsed)
		return (NULL);
	shell = TOK_NULL;
	if (is_there_pipes(tokens_parsed))
		shell = TOK_SHELL;
	root = build_binary_tree(tokens_parsed, shell);
	if (!root)
		return (NULL);
	return (root);
}

int	launch_program(char *user_input, t_env_ms *env_ll)
{
	t_node_ms	*root;
	int			ret;

	ret = 0;
	if (user_input[0] == '\0')
		return (ret);
	root = parsing(user_input, env_ll);
	if (!root)
		return (-1);
	free(user_input);
	ret = launch_exec(root, env_ll);
	free_binary_tree(root);
	return (ret);
}
