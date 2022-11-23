#include "../../includes/minishell.h"

t_redir_ms	*ft_lstnew_redir(char *file_name, t_tokens mode)
{
	t_redir_ms	*elem;

	elem = malloc(sizeof(t_redir_ms));
	if (elem == NULL)
		return (NULL);
	elem->file_name = file_name;
	elem->mode = mode;
	elem->next = NULL;
	return (elem);
}
