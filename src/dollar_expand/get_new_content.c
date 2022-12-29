#include "../../includes/minishell.h"

static int	get_length_without_spaces(char *value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (value[i] == ' ' && value[i])
		i++;
	while (value[i])
	{
		if (value[i] == ' ' && value[i + 1] != ' ')
			len++;
		if (value[i] == ' ')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*parse_spaces(char *value)
{
	char	*value_parsed;
	int		len_value_parsed;
	int		i;
	int		j;

	len_value_parsed = get_length_without_spaces(value);
	value_parsed = malloc((len_value_parsed + 1) * sizeof(char));
	if (!value_parsed)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] == ' ' && value[i])
		i++;
	while (j < len_value_parsed)
	{
		if (value[i] == ' ' && value[i + 1] != ' ')
			value_parsed[j++] = value[i];
		if (value[i] == ' ')
			i++;
		else
			value_parsed[j++] = value[i++];
	}
	value_parsed[j] = '\0';
	return (value_parsed);
}

static char	*get_new_parsed(char *parsed, char *value, int key_len, int i)
{
	char	*new_parsed;
	char	*value_parsed;

	if (value)
	{
		value_parsed = parse_spaces(value);
		if (!value_parsed)
			return (NULL);
	}
	else
		value_parsed = NULL;
	new_parsed = ft_strndup(parsed, i);
	if (!new_parsed)
	{
		free(value_parsed);
		return (NULL);
	}
	new_parsed = join_and_manage_dollar(new_parsed, parsed, \
		value_parsed, key_len, i);
	free(value_parsed);
	return (new_parsed);
}

char	*get_new_content(char *parsed, char *key, char *value, int nb_dollars)
{
	char	*new_parsed;
	int		key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (parsed[i])
	{
		if (parsed[i] == '$')
			nb_dollars--;
		if (parsed[i] == '$' && !nb_dollars)
		{
			new_parsed = get_new_parsed(parsed, value, key_len, i);
			return (new_parsed);
		}
		i++;
	}
	return (parsed);
}
