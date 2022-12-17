#include "../../includes/minishell.h"

static t_enum_token	*cpy_operators(t_enum_token *operators)
{
	t_enum_token	*operators_tmp;

	operators_tmp = malloc(2 * sizeof(t_enum_token));
	if (!operators_tmp)
		return (NULL);
	operators_tmp[0] = operators[0];
	operators_tmp[1] = operators[1];
	return (operators_tmp);
}

/*******************************************/
/*   left_branch :                         */
/*                                         */
/*   Launch the recursive for the          */
/*   left branch                           */
/*                                         */
/*   operators[0] represents the infile    */
/*   of the command                        */
/*   operators[1] represents the outfile   */
/*   of the command                        */
/*******************************************/

t_node_ms	*left_branch(t_token_ms *tokens, t_enum_token oper, t_enum_token shell, \
	t_enum_token *operators)
{
	t_node_ms	*binary_tree;
	t_enum_token	*operators_tmp;
	t_enum_token	shell_tmp;

	shell_tmp = shell;
	if (shell == TOK_SHELL)
	{
		if (check_parenthesis(tokens) == TOK_SUBSHELL)
			shell_tmp = TOK_SUBSHELL;
	}
	operators_tmp = cpy_operators(operators);
	if (!operators_tmp)
		return (NULL);
	if (oper == TOK_PIPE)
		operators_tmp[1] = oper;
	else
		operators_tmp[1] = TOK_NULL;
	binary_tree = build_binary_tree(tokens, shell_tmp, operators_tmp);
	free(operators_tmp);
	return (binary_tree);
}
