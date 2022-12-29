#include "../../includes/minishell.h"

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

static t_env_ms	*modify_value(char *content, t_env_ms *env)
{
	free(env->value);
	env->value = ft_strdup(content);
	if (!env->value)
	{
		perror(NULL);
		return (NULL);
	}
	return (env);
}

static t_env_ms	*append_value(char *content, t_env_ms *env)
{
	env->value = ft_strjoin_free_first(env->value, content);
	if (!env->value)
	{
		perror(NULL);
		return (NULL);
	}
	return (env);
}

static t_env_ms	*get_new_value_if_needed(char *content, t_env_ms *env)
{
	int	index_equal;

	index_equal = get_delim_sign_index(content);
	if (!ft_strncmp(env->key, content, index_equal))
	{
		if (content[index_equal] == '+')
			env = append_value(content + index_equal + 2, env);
		else if (content[index_equal] == '=')
			env = modify_value(content + index_equal + 1, env);
	}
	return (env);
}

t_env_ms	*change_value(char *content, t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (env)
	{
		env = get_new_value_if_needed(content, env);
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
