#include "../includes/minishell.h"

int	launch_program(char **user_input, char **env)
{
	t_node_ms		*binary_tree;
	t_token_ms		*tokens;
	t_tokens		shell;
	//t_context_ms	*cmd_lst;
	/*if (ft_check_syntax_error(user_input) == -1)
		return (-1);*/
	tokens = lexer(*user_input);
	if (!tokens)
		return (-1);
	tokens = parsing(tokens, env);
	if (!tokens)
		return (-1);
	shell = check_parenthesis(tokens);
	binary_tree = build_binary_tree(tokens, shell);
	if (!binary_tree)
		return (-1);
	return (0);
}
