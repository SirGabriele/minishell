#include "../includes/minishell.h"

/*tout bon*/
static void	free_env(t_env_ms *env)
{
	t_env_ms	*current;
	t_env_ms	*next;
	
	current = env;
	while (current != NULL)
	{
		next = current->next;
		if (current->key != NULL)
			free(current->key);
		if (current->value != NULL)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_program(t_node_ms *root, t_env_ms *env)
{
	(void)root;
	free_env(env);
}
