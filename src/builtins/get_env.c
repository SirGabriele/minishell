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

static int	get_delim_sign_index(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

t_env_ms	*get_env(char *content)
{
	t_env_ms	*env;
	int			index_delim;

	env = lstnew_env();
	if (!env)
		return (NULL);
	index_delim = get_delim_sign_index(content);
	env->key = ft_strndup(content, index_delim);
	if (!env->key)
		return (NULL);
	env->value = NULL;
	if (content[index_delim])
	{
		env->value = ft_strdup(content + index_delim + 1);
		if (!env->value)
		{
			free(env->key);
			perror(NULL);
		}
	}
	return (env);
}
