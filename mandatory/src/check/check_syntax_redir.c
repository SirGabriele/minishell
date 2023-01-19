/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:53:45 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/19 16:48:22 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	does_key_exist(char *key, t_env_ms *env_ll)
{
	t_env_ms	*cursor;

	if (key[0] == '?' || key[0] == '_' || key[0] == '0')
		return (0);
	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strcmp(cursor->key, key) == 0)
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

static int	is_ambiguous_redir(char *content, t_env_ms *env_ll)
{
	char	*key;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && should_expand_this_dollar(content, i) == 0)
		{
			key = get_key_to_expand(content + i + 1);
			ret = does_key_exist(key, env_ll);
			i += ft_strlen(key);
			free(key);
		}
		i++;
	}
	return (ret);
}

static int	check_ambiguous_redir(t_token_ms *tokens, t_env_ms *env_ll)
{
	while (tokens != NULL)
	{
		if ((tokens->type == TOK_TRUNC || tokens->type == TOK_APPEND
				|| tokens->type == TOK_INFILE || tokens->type == TOK_HEREDOC)
			&& tokens->next && tokens->next->type == TOK_STRING)
		{
			if (is_ambiguous_redir(tokens->next->content, env_ll) == 1)
			{
				ft_printf_fd(2, "minishell: %s: ambiguous redirect\n",
					tokens->next->content);
				set_exit_code(env_ll, 1);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	check_redir(t_token_ms *tokens, t_env_ms *env_ll)
{
	if (check_ambiguous_redir(tokens, env_ll) == -1)
		return (-1);
	while (tokens != NULL)
	{
		if (tokens->type == TOK_TRUNC || tokens->type == TOK_APPEND
			|| tokens->type == TOK_INFILE || tokens->type == TOK_HEREDOC)
		{
			if (!tokens->next)
			{
				print_checking_error_msg("newline");
				set_exit_code(env_ll, 2);
				return (-1);
			}
			else if (tokens->next && tokens->next->type != TOK_STRING)
			{
				print_checking_error_msg(tokens->next->content);
				set_exit_code(env_ll, 2);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
