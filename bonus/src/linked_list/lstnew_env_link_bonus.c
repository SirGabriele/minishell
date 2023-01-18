#include "../../includes/minishell_bonus.h"

t_env_ms	*lstnew_env_link(void)
{
	t_env_ms	*env_link;

	env_link = malloc(sizeof(t_env_ms));
	if (!env_link)
	{
		perror(NULL);
		return (NULL);
	}
	env_link->key = NULL;
	env_link->value = NULL;
	env_link->next = NULL;
	return (env_link);
}
