#include "../../includes/minishell.h"

static int	get_length_parsed_string(char *content)
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

static char *parse_content(char *parsed, char *content)
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
	return (parsed);
}

static char	*get_string_parsed(char *content, t_token_ms *tokens)
{
	char	*parsed;

	parsed = malloc((get_length_parsed_string(content) + 1) * sizeof(char));
	if (!parsed)
	{
		ft_putstr_fd("Error : malloc could not be done\n", 2);
		return (NULL);
	}
	parsed = parse_content(parsed, content);
	parsed = parse_spaces(parsed, tokens);
	free(content);
	return (parsed);
}

t_token_ms	*parsing(t_token_ms *tokens)
{
	t_token_ms		*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens->next)
	{
		//tmp_tokens->content = manage_dollar_sign();
		tmp_tokens->content = get_string_parsed(tmp_tokens->content, tokens);
		if (!tmp_tokens->content)
		{
			free_tokens(tokens);
			return (NULL);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (tokens);
}
