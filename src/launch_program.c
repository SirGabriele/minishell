#include "../includes/minishell.h"

int	launch_program(char **user_input, char **env)
{
	t_node_ms		*binary_tree;
	t_token_ms		*tokens;
	t_tokens		shell;

	tokens = lexer(*user_input, env);
	if (!tokens)
		return (-1);
	tokens = parsing(tokens);
	if (!tokens)
		return (-1);
	shell = check_parenthesis(tokens);
	binary_tree = build_binary_tree(tokens, shell);
	if (!binary_tree)
		return (-1);
	free_binary_tree(binary_tree);
	return (0);
}
