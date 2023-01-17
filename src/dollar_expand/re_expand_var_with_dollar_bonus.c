#include "../../includes/minishell.h"

static int	count_nb_dollar(char *content)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_dollar_value(char *content, int i, t_env_ms *env_ll)
{
	char	*key;
	char	*value;

	key = get_key_to_expand(content + i + 1);
	if (!key)
		return (NULL);
	value = get_key_value(env_ll, key);
	if (value == NULL && ft_strcmp(key, "0") == 0)
		value = ft_strdup("minishell");
	else if (value == NULL && ft_strcmp(key, "_") == 0)
		value = get_dollar_underscore(env_ll);
	free(key);
	return (value);
}

static char	*dollar_detected(char *content, t_env_ms *env_ll)
{
	char	*new_content;
	char	*value;
	int		i;
	int		j;

	i = 0;
	new_content = NULL;
	value = NULL;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && !what_is_dollar_in(content, i)
			&& examine_dollar_conditions(content, i) != 1)
			break ;
		else
			i++;
	}
	new_content = ft_strndup(content, i);
	if (count_nb_dollar(content + i) == 0)
	{
		new_content = ft_strjoin_free_first(new_content, content + i);
		return (new_content);
	}
	while (content[i] != '\0' && count_nb_dollar(content + i) != 0)
	{
		if (content[i] == '$' && !what_is_dollar_in(content, i)
			&& examine_dollar_conditions(content, i) != 1)
		{
			value = extract_dollar_value(content, i, env_ll);
			if (new_content == NULL)
			{
				new_content = ft_strdup(value);
				free(value);
			}
			else
			{
				new_content = ft_strjoin_free_first(new_content, value);
				free(value);
			}
		}
		i++;
	}
	j = 0;
	if (content[i] != '\0')
	{
		while (ft_isdigit(content[i + j]) != 1
			&& content[i + j] != ' ' && content[i + j] != '\"'
			&& content[i + j] != '$' && content[i + j] != '\0'
			&& content[i + j] != '\'' && content[i + j] != '='
			&& content[i + j] != '-' && content[i + j] != '?'
			&& content[i + j] != '_')
			i++;
		if (content[i + j] == '0' || content[i + j] == '_')
			i++; 
		while (content[i + j] != '\0')
			j++;
		new_content = ft_strnjoin_free_first(new_content, content + i, j);
	}
	free(content);
	return (new_content);
}

void	re_expand_var_with_dollar(char **content, t_env_ms *env_ll)
{
	int	i;

	i = 0;
	while (content[i] != NULL)
	{
		if (count_nb_dollar(content[i]) != 0)
			content[i] = dollar_detected(content[i], env_ll);
		i++;
	}
}
