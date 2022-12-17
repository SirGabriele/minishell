#include "../includes/minishell.h"

int	launch_program(char **user_input, t_env_ms *env_ll)
{
	t_node_ms		*root;
	t_token_ms		*tokens;

	if (*user_input[0] == '\0')
		return (0);
//	set_exit_code_to(env_ll, 0);
	tokens = lexer(*user_input, env_ll);
	if (!tokens)
		return (-1);
	tokens = parse_quotes(tokens);
	if (!tokens)
		return (-1);
	root = start_binary_tree(tokens);
	if (!root)
		return (-1);
	if (launch_exec(root, env_ll) == -1)
		return (-1);
	free_binary_tree(root);
	return (0);
}
