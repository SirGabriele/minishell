#include "../../includes/minishell.h"

t_token_ms	*increm_tokens_copy(t_token_ms *tokens_cpy)
{
	while (tokens_cpy->type != TOK_PIPE && tokens_cpy->type != TOK_OR_OPER
		&& tokens_cpy->type != TOK_AND_OPER && tokens_cpy->next)
		tokens_cpy = tokens_cpy->next;
	if (tokens_cpy->next)
		tokens_cpy = tokens_cpy->next;
	return (tokens_cpy);
}

int	length_without_spaces(char *pipeline)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ft_isspace(pipeline[i]) && pipeline[i])
		i++;
	len = i;
	while (pipeline[i])
		i++;
	while (ft_isspace(pipeline[i - 1]) && i)
		i--;
	len = i - len;
	return (len);
}

char	*add_space_if_needed(char *pipeline, t_token_ms *tokens)
{
	if (tokens->next->type != TOK_PIPE && tokens->next->type != TOK_OR_OPER
		&& tokens->next->type != TOK_AND_OPER && tokens->next->type)
	{
		if (tokens->type == TOK_STRING && tokens->next->type != TOK_CL_PAR)
			pipeline = ft_strjoin(pipeline, " ");
		else if (tokens->type == TOK_CL_PAR 
			&& tokens->next->type != TOK_CL_PAR)
			pipeline = ft_strjoin(pipeline, " ");
	}
	return (pipeline);
}

char	*parse_spaces(char *pipeline, t_token_ms *tokens)
{
	char	*dst;
	int		i;
	int		j;
	int		len_without_spaces;

	i = 0;
	j = 0;
	len_without_spaces = length_without_spaces(pipeline);
	dst = malloc((len_without_spaces + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (ft_isspace(pipeline[i]) && pipeline[i])
		i++;
	while (j < len_without_spaces)
		dst[j++] = pipeline[i++];
	dst[j] = '\0';
	free(pipeline);
	dst = add_space_if_needed(dst, tokens);
	return (dst);
}
