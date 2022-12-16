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

static t_env_ms	*modify_value(char *content, t_env_ms *env)
{
	free(env->value);
	env->value = malloc((ft_strlen(content) + 1) * sizeof(char));
	if (!env_value)
		return (NULL);
	ft_strcpy(env->value, content);
	return (env);
}

static t_env_ms	*change_value_if_needed(char **content, t_env_ms *env)
{
	int	i;
	int	index_equal;

	i = 0;
	while (content[i])
	{
		index_equal = get_equal_sign_index(content[i]);
		if (!ft_strncmp(env->key, content[i], index_equal))
		{
			env = modify_value(content[i] + index_equal, env);
			if (!env)
				return (NULL);
			return (env);
		}
		i++;
	}
	return (env);
}

t_env_ms	*change_value_if_key_exists(char **content, t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (env)
	{
		env = change_value_if_needed(content, env);
		if (!env)
		{
			free_env_list(tmp_env);
			perror(NULL);
			return (NULL);
		}
		env = env->next;
	}
	return (tmp_env);
}
