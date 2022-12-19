#include "../../includes/minishell.h"

static int	get_equal_sign_index(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (i);
	}
	return (i);
}

t_env_ms	*get_env(char *content, t_env_ms *env)
{
	char	*key;
	char	*value;
	int		index_equal;

	index_equal = get_equal_sign_index(content);
	env->key = malloc((index_equal + 1) * sizeof(char));
	if (!env->key)
		return (NULL);
	env->value = malloc((ft_strlen(content) - index_equal + 1) * sizeof(char));
	if (!env->value)
	{
		free(env->key);
		perror(NULL);
	}
	ft_strncpy(env->key, content, index_equal);
	ft_strncpy(env->value, content, ft_strlen(content) - index_equal);
	return (env);
}
