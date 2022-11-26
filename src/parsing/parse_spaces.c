#include "../../includes/minishell.h"

static int	length_without_spaces(char *pipeline)
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

static char	*add_space_if_needed(char *pipeline, t_token_ms *tokens)
{
	if (tokens->next->type != TOK_PIPE && tokens->next->type != TOK_OR_OPER
		&& tokens->next->type != TOK_AND_OPER && tokens->next->type)
	{
		if (tokens->type == TOK_STRING && tokens->next->type != TOK_CL_PAR)
			pipeline = ft_strjoin_free_first(pipeline, " ");
		else if (tokens->type == TOK_CL_PAR 
			&& tokens->next->type != TOK_CL_PAR)
			pipeline = ft_strjoin_free_first(pipeline, " ");
		else if (tokens->type == TOK_INFILE && TOK_STRING)
			pipeline = ft_strjoin_free_first(pipeline, " ");
		else if (tokens->type == TOK_TRUNC && TOK_STRING)
			pipeline = ft_strjoin_free_first(pipeline, " ");
		else if (tokens->type == TOK_HEREDOC && TOK_STRING)
			pipeline = ft_strjoin_free_first(pipeline, " ");
		else if (tokens->type == TOK_APPEND && TOK_STRING)
			pipeline = ft_strjoin_free_first(pipeline, " ");
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
	dst = add_space_if_needed(dst, tokens);
	if (!dst)
		return (NULL);
	free(pipeline);
	return (dst);
}
