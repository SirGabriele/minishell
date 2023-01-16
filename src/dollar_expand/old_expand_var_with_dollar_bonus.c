#include "../../includes/minishell.h"

static char	*expand_dollar(char *parsed, char *unparsed, int i, \
	t_env_ms *env_ll)
{
	char	*expanded_content;
	char	*key;
	char	*value;
	int		nb_dollars;

	key = get_key_to_expand(unparsed + i + 1);
	if (!key)
		return (NULL);
	value = get_key_value(env_ll, key);
	expanded_content = ft_strdup(value);
	free(key);
	return (new_parsed);
}

static char	*get_content_with_env_values(char *content, t_env_ms *env_ll)
{
	char	*key;
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$' && !what_is_dollar_in(content, i)
			&& examine_dollar_conditions(content, i) != 1)
			content = expand_dollar(content, i, env_ll);
		i++;
	}
	return (content);
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

t_token_ms	*old_expand_var_with_dollar(char **content, t_env_ms *env_ll)
{
	int	i;

	i = 0;
	while (content[i] != NULL)
	{
		if (ft_strncmp(content[i], "<<", 2) == 0
			i++;
		else
			content[i] = get_content_with_env_values(content[i], env_ll);
		i++;
	}
	return (tmp_tokens);
}
