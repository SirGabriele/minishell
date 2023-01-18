#include "../../includes/minishell_bonus.h"

static int	check_syntax(char **user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens;

	tokens = lexer(*user_input);
	if (check_syntax_first_token(tokens, env_ll) == -1
		|| check_syntax_par(tokens, env_ll) == -1
		|| check_casual_syntax_error(user_input, env_ll) == -1)
	{
		free_tokens(tokens);
		return (-1);
	}
	free_tokens(tokens);
	return (0);
}

static int	complete_user_input(char **user_input, t_env_ms *env_ll)
{
	char		*new_user_input;
	t_token_ms	*tokens;
	int			ret;

	ret = 0;
	tokens = lexer(*user_input);
	if (!tokens)
		ret = -1;
	if (check_syntax_pipe(tokens, env_ll) == -1 || check_syntax_par(tokens, env_ll) == -1
		|| check_syntax_and_or(tokens, env_ll) == -1)
		return (-1);
	if (is_last_pipes_closed(tokens) == -1 || is_last_token_and_or(tokens) == 0)
	{
		new_user_input = get_missing_pipe_input(*user_input);
		if (new_user_input == NULL)
			ret = 3;
		else
		{
			free(*user_input);
			*user_input = new_user_input;
			ret = 1;
		}
	}
	free_tokens(tokens);
	return (ret);
}

int	ft_check_all_syntax_error(char **user_input, t_env_ms *env_ll)
{
	int	condition;

	condition = 1;
	while (condition != 0)
	{
		condition = 0;
		if (ft_check_isolated_quotes(*user_input, env_ll) == -1)
			return (1);
		if (check_syntax(user_input, env_ll) == -1)
			return (2);
		condition = complete_user_input(user_input, env_ll);
		if (condition == -1)
			return (-1);
		else if (condition == 3)
			return (3);
	}
	return (0);
}
