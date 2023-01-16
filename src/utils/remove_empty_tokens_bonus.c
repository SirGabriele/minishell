#include "../../includes/minishell.h"

t_token_ms	*remove_empty_tokens(t_token_ms *tokens)
{
	t_token_ms	*cursor;
	t_token_ms	*head;

	while (tokens && tokens->content && tokens->content[0] == '\0')
	{
		cursor = tokens->next;
		free(tokens->content);
		tokens->content = NULL;
		free(tokens);
		tokens = NULL;
		tokens = cursor;
	}
	head = tokens;
	while (tokens != NULL)
	{
		cursor = tokens->next;
		if (cursor && cursor->content && cursor->content[0] == '\0')
		{
			tokens->next = cursor->next;
			tokens = cursor->next;
			free(cursor->content);
			cursor->content = NULL;
			free(cursor);
			cursor = NULL;
		}
		else
			tokens = tokens->next;
	}
	return (head);
}
