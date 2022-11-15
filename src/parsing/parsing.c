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
		ft_putstr_fd("Error : malloc could not be done\n", 2);
		return (NULL);
	}
	parsed = parse_content(parsed, content);
	free(content);
	return (parsed);
}

void	print_type(t_tokens type)
{
	if (type == 0)
		printf("	type = TOK_NULL\n");
	else if (type == 1)
		printf("	type = TOK_STRING\n");
	else if (type == 2)
		printf("	type = TOK_OP_PAR\n");
	else if (type == 3)
		printf("	type = TOK_CL_PAR\n");
	else if (type == 4)
		printf("	type = TOK_INFILE\n");
	else if (type == 5)
		printf("	type = TOK_OUTF_TRUNC\n");
	else if (type == 6)
		printf("	type = TOK_HEREDOC\n");
	else if (type == 7)
		printf("	type = TOK_OUTF_APPEND\n");
	else if (type == 8)
		printf("	type = TOK_PIPE\n");
	else if (type == 9)
		printf("	type = TOK_AND_OPER\n");
	else if (type == 10)
		printf("	type = TOK_OR_OPER\n");
}

void	print_tokens(t_token_ms *tokens)
{
	int	i;

	i = 1;
	while (tokens->next)
	{
		printf("\ntoken %d :\n", i);
		print_type(tokens->type);
		printf("	content = %s\n", tokens->content);
		tokens = tokens->next;
		i++;
	}
	printf("\n");
}

int	parsing(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens->next)
	{
		if (tmp_tokens->type == TOK_STRING)
		{
			tmp_tokens->content = get_string_parsed(tmp_tokens->content);
			if (!tmp_tokens->content)
			{
				free_tokens(tokens);
				return (-1);
			}
		}
		tmp_tokens = tmp_tokens->next;
	}
	//print_tokens(tokens); //a supprimer
	return (0);
}
