/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_with_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:39:14 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/19 00:50:41 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_dollar(char *parsed, char *unparsed, int i, \
	t_env_ms *env_ll)
{
	char	*key;
	char	*value;
	char	*new_parsed;
	int		nb_dollars;

	key = get_key_to_expand(unparsed + i + 1);
	if (!key)
	{
		free(parsed);
		return (NULL);
	}
	nb_dollars = get_nb_dollars(unparsed, i);
	value = get_key_value(env_ll, key);
	new_parsed = get_new_content(parsed, key, value, nb_dollars);
	free(key);
	free(parsed);
	parsed = NULL;
	return (new_parsed);
}

static char	*delete_dollar(char *parsed, char *unparsed, int i)
{
	char	*new_parsed;
	int		nb_dollars;
	int		j;

	new_parsed = NULL;
	nb_dollars = get_nb_dollars(unparsed, i);
	j = 0;
	while (parsed[j])
	{
		if (parsed[j] == '$')
			nb_dollars--;
		if (parsed[j] == '$' && !nb_dollars)
		{
			new_parsed = ft_strndup(parsed, j);
			if (new_parsed)
				new_parsed = ft_strjoin_free_first(new_parsed, parsed + j + 1);
			if (!new_parsed)
				free(parsed);
			free(parsed);
			return (new_parsed);
		}
		j++;
	}
	free(parsed);
	return (new_parsed);
}

static char	*expand_according_to_dollar_conditions(char *parsed, \
	char *unparsed, int i, t_env_ms *env_ll)
{
	char	*key;

	key = get_key_to_expand(unparsed + i + 1);
	if (examine_dollar_conditions(unparsed, i) == 2
		|| key[0])
		parsed = expand_dollar(parsed, unparsed, i, env_ll);
	else if (examine_dollar_conditions(unparsed, i) == 3)
		parsed = delete_dollar(parsed, unparsed, i);
	free(key);
	return (parsed);
}

static char	*get_content_with_env_values(char *parsed, char *unparsed, \
	t_env_ms *env_ll)
{
	char	*key;
	int		i;

	i = 0;
	while (unparsed[i])
	{
		if (unparsed[i] == '$' && !what_is_dollar_in(unparsed, i)
			&& examine_dollar_conditions(unparsed, i) != 1)
		{
			parsed = expand_according_to_dollar_conditions(parsed, \
				unparsed, i, env_ll);
			if (!parsed)
				return (NULL);
			key = get_key_to_expand(unparsed + i + 1);
			if (examine_dollar_conditions(unparsed, i) == 2
				|| examine_dollar_conditions(unparsed, i) == 3 || key[0])
				unparsed[i] = '0';
			free(key);
		}
		i++;
	}
	return (parsed);
}

/****************************************************************/
/*                                                     			*/
/*  Verifies if the variable after the dollar sign is a valid	*/
/*		environment variable. If it is, the dollar is expanded.	*/
/*		Otherwise, the dollar and the variable are deleted from	*/
/*		the line												*/
/*                                                     	 		*/
/*  Parameters:													*/
/*		content	-	line from the terminal						*/
/*		env		-	env variables								*/
/*																*/
/*  Return:														*/
/*		content	-	the newly formed line						*/
/*																*/
/****************************************************************/

t_token_ms	*expand_var_with_dollar(t_token_ms *tokens_unparsed, \
	t_token_ms *tokens_parsed, t_env_ms *env_ll)
{
	t_token_ms	*tmp_parsed;
	t_token_ms	*tmp_unparsed;

	tmp_parsed = tokens_parsed;
	tmp_unparsed = tokens_unparsed;
	while (tokens_unparsed)
	{
		tokens_parsed->content = get_content_with_env_values
			(tokens_parsed->content, tokens_unparsed->content, env_ll);
		if (!tokens_parsed->content)
		{
			free_tokens(tmp_parsed);
			free_tokens(tmp_unparsed);
			return (NULL);
		}
		if (tokens_parsed->type == TOK_HEREDOC && tokens_parsed->next)
		{
			tokens_parsed = tokens_parsed->next;
			tokens_unparsed = tokens_unparsed->next;
		}
		tokens_parsed = tokens_parsed->next;
		tokens_unparsed = tokens_unparsed->next;
	}
	return (tmp_parsed);
}
