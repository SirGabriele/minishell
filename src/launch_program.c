#include "../includes/minishell.h"

int	launch_program(char **user_input, t_env_ms *env_ll)
{
	t_node_ms       *root;
	t_token_ms      *tokens_unparsed;
	t_token_ms      *tokens_parsed;

	if (*user_input[0] == '\0')
		return (0);
//	set_exit_code_to(env_ll, 0);
	tokens_unparsed = lexer(*user_input);
	tokens_parsed = lexer(*user_input);
	if (!tokens_parsed)
		return (-1);
	tokens_parsed = parse_quotes(tokens_parsed);
	if (!tokens_parsed)
		return (-1);
	tokens_parsed = expand_var_with_dollar(tokens_unparsed, tokens_parsed, \
		env_ll);
	if (!tokens_parsed)
		return (-1);
	root = start_binary_tree(tokens_parsed);
	if (!root)
		return (-1);
	if (launch_exec(root, env_ll) == -1)
	{
		free_binary_tree(root);
		return (-1);
	}
	free_binary_tree(root);
	free_tokens(tokens_unparsed);
	return (0);
}
