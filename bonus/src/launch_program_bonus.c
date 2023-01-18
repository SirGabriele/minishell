#include "../includes/minishell_bonus.h"

static t_node_ms	*parsing(char *user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens_unparsed;
	t_token_ms	*tokens_parsed;
	t_node_ms	*root;
	(void)env_ll;

	tokens_unparsed = lexer(user_input);
	tokens_parsed = lexer(user_input);
	if (!tokens_unparsed || !tokens_parsed)
		return (NULL);
	tokens_parsed = parse_quotes(tokens_parsed);
	if (!tokens_parsed)
		return (NULL);
	tokens_parsed = expand_var_with_dollar(tokens_unparsed, tokens_parsed, \
		env_ll);
	if (!tokens_parsed)
		return (NULL);
	root = start_binary_tree(tokens_parsed);
	if (!root)
		return (NULL);
	free_tokens(tokens_unparsed);
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
