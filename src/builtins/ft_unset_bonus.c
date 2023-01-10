#include "../../includes/minishell.h"

static int    is_invalid_identifier(char *content)
{
	int	i;

	i = 0;
	while (content[i])
    {
        if (content[i] == '~' || content[i] == '#' || content[i] == ' '
            || content[i] == '{' || content[i] == '[' || content[i] == '-'
            || content[i] == '^' || content[i] == '@' || content[i] == ']'
            || content[i] == '}' || content[i] == '*' || content[i] == '%'
            || content[i] == '!' || content[i] == ':' || content[i] == '/'
            || content[i] == '.' || content[i] == '?' || content[i] == ',')
		{
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
				content[i]);
            return (1);
		}
		i++;
	}
	return (0);
}

static int	delete_next_link(t_env_ms *env, char *content)
{
	t_env_ms	*tmp;

	if (ft_strcmp(content, env->next->key) == 0)
	{
		tmp = env->next->next;
		free(env->next->key);
		free(env->next->value);
		free(env->next);
		env->next = tmp;
		return (0);
	}
	return (1);
}

int	ft_unset(char **content, t_env_ms **env)
{
	t_env_ms	*tmp_env;
	int			i;
	int			ret;

	ret = 0;
	i = 0;
	tmp_env = *env;
	while (content[i])
	{
		ret = is_invalid_identifier(content[i]);
		if (ret == 1)
		{
			i++;
			continue ;
		}
		while ((*env)->next)
		{
			ret = delete_next_link(*env, content[i]);
			if (ret == 0)
				break ;
			if ((*env)->next)
				*env = (*env)->next;
		}
		*env = tmp_env;
		i++;
	}
	return (ret);
}
