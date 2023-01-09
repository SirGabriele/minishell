#include "../includes/minishell.h"

int	check_syntax_error(t_token_ms *tokens_unparsed)
{
	t_token_ms	*cursor;

	cursor = tokens_unparsed;
	while (cursor != NULL)
	{
		if (cursor->type == TOK_AND_OPER || cursor->type == TOK_OR_OPER
			|| cursor->type == TOK_TRUNC || cursor->type == TOK_APPEND
			|| cursor->type == TOK_INFILE || cursor->type == TOK_HEREDOC
			|| (cursor->type == TOK_OP_PAR && !cursor->next))
		{
			if (!cursor->next && cursor->type != TOK_CL_PAR)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				return (-1);
			}
			else if ((cursor->next && cursor->next->type != TOK_STRING)
				|| (cursor->type == TOK_OP_PAR && cursor->next->type == TOK_CL_PAR)
				|| (cursor->type == TOK_CL_PAR && cursor->next->type == TOK_OP_PAR))
			{
				ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
					cursor->next->content);
				return (-1);
			}
		}
		cursor = cursor->next;
	}
	return (0);
}

static int	parsing(t_node_ms **root, char *user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens_unparsed;
	t_token_ms	*tokens_parsed;

	tokens_unparsed = lexer(user_input);
	if (check_syntax_error(tokens_unparsed) == -1)
	{
		free_tokens(tokens_unparsed);
		set_exit_code(env_ll, 2);
		return (-2);
	}
	tokens_parsed = lexer(user_input);
	if (!tokens_parsed)
		return (-1);
	tokens_parsed = parse_quotes(tokens_parsed);
	if (!tokens_parsed)
		return (-1);
	tokens_parsed = expand_var_with_dollar(tokens_unparsed, tokens_parsed, \
		env_ll);
	if (!tokens_parsed)
		return (-1);
	*root = start_binary_tree(tokens_parsed);
	free_tokens(tokens_unparsed);
	return (0);
}

int	launch_program(char **user_input, t_env_ms *env_ll)
{
	t_node_ms	*root;
	int			ret;

	ret = 0;
	if (*user_input[0] == '\0')
		return (ret);
	ret = parsing(&root, *user_input, env_ll);
	if (ret != 0)
		return (ret);
	free(*user_input);
	if (launch_exec(root, env_ll) == -1)
		ret = -1;
	free_binary_tree(root);
	return (ret);
}
