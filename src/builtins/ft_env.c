#include "../../includes/minishell.h"

static int	get_nb_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}

static void	print_initialized_environment(t_env_ms *tmp_env)
{
	while (tmp_env)
	{
		if (tmp_env->value && ft_strncmp(tmp_env->value, "?", 1) != 0)
		{
			ft_printf_fd(0, "%s=", tmp_env->key);
			ft_printf_fd(0, "%s\n", tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
}

int	ft_env(char **content, t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	if (get_nb_args(content) == 0)
		print_initialized_environment(tmp_env);
	else
	{
		ft_printf_fd(2, "minishell: env: too many arguments\n");
		return (1);
	}
	return (0);
}
