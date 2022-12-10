#include "../../includes/minishell.h"

static t_token_ms	*incremente_half_1_if_needed(t_token_ms *half_1, int index_token)
{
	if (index_token > 1)
	{
		half_1->next = lstnew_token();
		if (!half_1->next)
			return (NULL);
		half_1 = half_1->next;
	}
	else
		half_1->next = NULL;
	return (half_1);
}

t_token_ms	*get_first_half(t_token_ms *tokens, int index_token)
{
	t_token_ms	*half_1;
	t_token_ms	*cpy_half_1;

	half_1 = lstnew_token();
	if (!half_1)
		return (NULL);
	cpy_half_1 = half_1;
	while (index_token)
	{
		half_1->content = NULL;
		half_1->content = ft_strjoin(half_1->content, tokens->content);
		if (!half_1->content)
			return (NULL);
		half_1->type = tokens->type;
		half_1 = incremente_half_1_if_needed(half_1, index_token);
		if (!half_1)
		{
			free_n_tokens(cpy_half_1, 0);
			return (NULL);
		}
		tokens = tokens->next;
		index_token--;
	}
	return (cpy_half_1);
}

