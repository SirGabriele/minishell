#include "../../includes/minishell.h"

t_token_ms	*ft_lstnew_token(void)
{
	t_token_ms	*elem;

	elem = malloc(sizeof(t_token_ms));
	if (!elem)
	{
		perror(NULL);
		return (NULL);
	}
	elem->type = 0;
	elem->content = NULL;
	elem->next = NULL;
	return (elem);
}
