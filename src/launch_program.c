#include "../includes/minishell.h"

int	launch_program(char **user_input, char **env)
{
	t_node_ms		*root;
	t_token_ms		*tokens;

	tokens = lexer(*user_input, env);
	if (!tokens)
		return (-1);
	tokens = parse_quotes(tokens);
	if (!tokens)
		return (-1);
	root = start_binary_tree(tokens);
	if (!root)
		return (-1);
	free_binary_tree(root);
	return (0);
}
