#include "../../includes/minishell.h"

static void	delete_link_if_needed(t_env_ms *env, char *content)
{
	t_env_ms	*tmp;
	int	len_content;

	len_content = ft_strlen(content);
	if (!ft_strncmp(content, env->next->key, len_content)
		&& !env->next->key[len_content])
	{
		tmp = env->next->next;
		free(env->next->key);
		free(env->next->value);
		free(env->next);
		env->next = tmp;
	}
}

int	ft_unset(char **content, t_env_ms **env)
{
	t_env_ms	**tmp_env;
	int	i;

	i = 0;
	tmp_env = env;
	if (content[0][0] == '-')
	{
		ft_printf_fd(2, "minishell: unset: invalid option\n");
		set_exit_code(*env, 2);
		return (2);
	}
	while (content[i])
	{
		while ((*env)->next)
		{
			delete_link_if_needed(*env, content[i]);
			if ((*env)->next)
				*env = (*env)->next;
		}
		*env = *tmp_env;
		i++;
	}
	set_exit_code(*env, 0);
	return (0);
}
