#include "../../includes/minishell.h"

t_env_ms	*extend_env_list(char *content, t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (env->next)
		env = env->next;
	env->next = get_env(content);
	if (!env)
		return (NULL);	
	return (tmp_env);
}
