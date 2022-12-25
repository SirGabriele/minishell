#include "../../includes/minishell.h"

static int	key_exists(char *content, t_env_ms *env)
{
	int	len;

	while (env)
	{
		len = ft_strlen(env->key);
		if (!ft_strncmp(content, env->key, len)
			&& (content[len] == '=' || content[len] == '+'))
			return (1);
		env = env->next;
	}
	return (0);
}

t_env_ms	*set_values_export(char **content, t_env_ms *env)
{
	int	i;

	i = 0;
	while (content[i])
	{	
		if (key_exists(content[i], env))
			env = change_value(content[i], env);
		else
			env = extend_env_list(content[i], env);
		if (!env)
		{
			perror(NULL);
			return (NULL);
		}
		i++;
	}
	return (env);
}
