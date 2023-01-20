/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:22 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/19 01:03:41 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	check_syntax(char **user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens;

	tokens = lexer(*user_input);
	if (check_syntax_first_token(tokens, env_ll) == -1
		|| check_syntax_par(tokens, env_ll) == -1
		|| check_syntax_redir(tokens, env_ll) == -1
		|| check_syntax_pipe(tokens, env_ll) == -1
		|| check_syntax_and_or(tokens, env_ll) == -1)
	{
		free_tokens(tokens);
		return (-1);
	}
	free_tokens(tokens);
	return (0);
}

static int	ft_check_all_syntax_error(char **user_input, t_env_ms *env_ll)
{
	if (ft_check_isolated_quotes(*user_input, env_ll) == -1)
		return (-1);
	if (check_syntax(user_input, env_ll) == -1)
		return (-1);
	return (0);
}

static int	is_exit(char *user_input)
{
	int	i;

	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (0);
	}
	i = 0;
	while (ft_isspace(user_input[i]) == 1)
		i++;
	if (ft_strncmp(user_input + i, "exit", 4) == 0)
	{
		while (ft_isspace(user_input[i + 4]) == 1)
			i++;
		if (user_input[i + 4] == '\0')
		{
			rl_clear_history();
			free(user_input);
			return (0);
		}
	}
	return (1);
}

static int	check_if_only_spaces(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (!ft_isspace(user_input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cmd_prompt(t_env_ms *env_ll)
{
	char	*input;
	int		ret;

	while (1)
	{
		g_signal = 0;
		set_signals_first_readline();
		input = readline("minishell$ ");
		if (g_signal == 130)
			set_exit_code(env_ll, 130);
		if (is_exit(input) == 0)
			return (0);
		ret = ft_check_all_syntax_error(&input, env_ll);
		if (input && !check_if_only_spaces(input) && ft_strlen(input) > 0)
			add_history(input);
		if (ret != 0)
		{
			free(input);
			continue ;
		}
		if (input && !check_if_only_spaces(input)
			&& launch_program(input, env_ll) == -1 && !ret)
			return (-1);
	}
	return (0);
}
