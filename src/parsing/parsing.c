#include "../../includes/minishell.h"

static int	length_parsed_string(char *content)
{
	int	i;
	int	i_cpy;
	int	length;

	i = 0;
	length = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			i_cpy = i;
			i++;
			while (content[i] != content[i_cpy] && content[i])
				i++;
			length += i - i_cpy - 1;
			i++;
		}
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

static char *parse_content(char *parsed, char *content, char **env)
{
	int	i;
	int	j;
	int	i_cpy;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			i_cpy = i;
			i++;
			while (content[i] != content[i_cpy] && content[i])
				parsed[j++] = content[i++];
			i++;
		}
		else
			parsed[j++] = content[i++];
	}
	parsed[j] = '\0';
	parsed = convert_var_with_dollar(parsed, content, env);
	return (parsed);
}

static char	*get_string_parsed(t_token_ms *tokens, char **env)
{
	char	*parsed;

	parsed = malloc((length_parsed_string(tokens->content) + 1) * sizeof(char));
	if (!parsed)
	{
		ft_putstr_fd("Error : malloc could not be done\n", 2);
		return (NULL);
	}
	parsed = parse_content(parsed, tokens->content, env);
	parsed = parse_spaces(parsed, tokens);
	free(tokens->content);
	return (parsed);
}

t_token_ms	*parsing(t_token_ms *tokens, char **env)
{
	t_token_ms		*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		tmp_tokens->content = get_string_parsed(tmp_tokens, env);
		if (!tmp_tokens->content)
		{
			free_tokens(tokens);
			return (NULL);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (tokens);
}
