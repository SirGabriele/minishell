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

static char	*parse_content(char *parsed, char *content)
{
	int	i;
	int	j;
	int	i_cpy;

	i = 0;
	j = 0;
	while (content[i])//a modifier incrementer quand on est sur une quote (utiliser what_is_index_in)
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

static char	*get_string_parsed(t_token_ms *tokens)
{
	char	*parsed;

	parsed = malloc((length_parsed_string(tokens->content) + 1) * sizeof(char));
	if (!parsed)
	{
		perror(NULL);
		return (NULL);
	}
	parsed = parse_content(parsed, tokens->content);
	if (!parsed)
		return (NULL);
	free(tokens->content);
	return (parsed);
}

/************************************************************/
/*															*/
/*	Definition:	Delete useless quotes						*/
/*															*/
/*	Parameters:												*/
/*		tokens - link list of tokens with potential useless	*/
/*				 quotes										*/
/*															*/
/*	Return:													*/
/*		tokens - link list without useless quotes			*/
/*		NULL - failure										*/
/*															*/
/************************************************************/

t_token_ms	*parse_quotes(t_token_ms *tokens)
{
	t_token_ms		*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		tmp_tokens->content = get_string_parsed(tmp_tokens);
		if (!tmp_tokens->content)
		{
			free_tokens(tokens);
			return (NULL);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (tokens);
}