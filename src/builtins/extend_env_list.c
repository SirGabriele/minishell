#include "../../includes/minishell.h"

static t_env_ms	*lstnew_env(void)
{
	t_env_ms	*env;

	env = malloc(sizeof(t_env_ms));
	if (!env)
		return (NULL);
	env->next = NULL;
	return (env);
}

t_env_ms	*extend_env_list(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		tmp_env = lstnew_env();
		tmp_env = get_env(content[i], tmp_env);
		if (!tmp_env)
			return (NULL);
		tmp_env = tmp_env->next;
		i++;
	}
}
