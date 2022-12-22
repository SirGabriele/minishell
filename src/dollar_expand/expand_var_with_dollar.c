#include "../../includes/minishell.h"

static char	*expand_dollar(char *parsed, char *unparsed, t_env_ms *env_ll, \
	int nb_dollars)
{
	char	*key;
	char	*value;
	char	*new_parsed;

	key = get_key_to_expand(unparsed + 1);
	if (!key)
	{
		free(parsed);
		return (NULL);
	}
	value = get_key_value(env_ll, key);
	new_parsed = get_new_content(parsed, key, value, nb_dollars);
	free(key);
	free(parsed);
	parsed = NULL;
	return (new_parsed);
}

static char	*delete_dollar(char *parsed, int nb_dollar)
{
	char	*new_parsed;
	int		i;

	i = 0;
	new_parsed = NULL;
	while (parsed[i])
	{
		if (parsed[i] == '$')
			nb_dollar--;
		if (parsed[i] == '$' && !nb_dollar)
		{
			new_parsed = ft_strndup(parsed, i);
			if (new_parsed)
				new_parsed = ft_strjoin_free_first(new_parsed, parsed + i + 1);
			if (!new_parsed)
				free(parsed);
			return (new_parsed);
		}
		i++;
	}
	free(parsed);
	return (new_parsed);
}

static char	*expand_according_to_dollar_conditions(char *parsed, \
	char *unparsed, t_env_ms *env_ll, int nb_dollars)
{
	if (examine_dollar_conditions(unparsed, 0) == 2
		|| !examine_dollar_conditions(unparsed, 0))
		parsed = expand_dollar(parsed, unparsed, env_ll, nb_dollars);
	else if (examine_dollar_conditions(unparsed, 0) == 3)
		parsed = delete_dollar(parsed, nb_dollars);
	return (parsed);
}

static char	*get_content_with_env_values(char *parsed, char *unparsed, \
	t_env_ms *env_ll)
{
	char	*old_parsed;
	int		i;
	int		nb_dollars;

	i = 0;
	nb_dollars = 0;
	while (unparsed[i])
	{
		if (unparsed[i] == '$')
			nb_dollars++;
		if (unparsed[i] == '$' && !what_is_dollar_in(unparsed, i))
		{
			old_parsed = parsed;
			parsed = expand_according_to_dollar_conditions(parsed, \
				unparsed + i, env_ll, nb_dollars);
			if (!parsed)
				return (NULL);
			if (get_diff_nb_dollars(old_parsed, parsed))
				nb_dollars--;

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
	t_token_ms	*tmp_tokens;

	tmp_tokens = tokens_parsed;
	while (tokens_unparsed)
	{
		tokens_parsed->content = get_content_with_env_values
			(tokens_parsed->content, tokens_unparsed->content, env_ll);
		if (!tokens_parsed->content)
		{
			free_tokens(tmp_tokens);
			free_tokens(tokens_unparsed);
			return (NULL);
		}
		tokens_parsed = tokens_parsed->next;
		tokens_unparsed = tokens_unparsed->next;
	}
	return (tmp_tokens);
}
