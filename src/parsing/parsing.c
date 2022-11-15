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
	return (parsed);
}

static char	*get_string_parsed(char *content)
{
	char	*parsed;

	parsed = malloc((get_length_parsed_string(content) + 1) * sizeof(char));
	if (!parsed)
	{
		ft_printf_error("Error : malloc could not be done\n");
		return (NULL);
	}
	parsed = parse_content(parsed, content);
	free(content);
	return (parsed);
}

int	parsing(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;
	int	i = 1; //a supprimer

	tmp_tokens = tokens;
	while (tmp_tokens->next)
	{
		if (tmp_tokens->type == TOK_STRING)
		{
			tmp_tokens->content = get_string_parsed(tmp_tokens->content);
			if (!tmp_tokens->content)
				return (-1);
		}
		ft_printf("token %d : content = %s\n", i, tmp_tokens->content); //a supprimer
		i++; //a supprimer
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}
