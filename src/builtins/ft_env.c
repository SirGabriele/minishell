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
		if (tmp_env->value && ft_strcmp(tmp_env->key, "?"))
		{
			ft_printf_fd(0, "%s=", tmp_env->key);
			ft_printf_fd(0, "%s\n", tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
}

t_env_ms	**ft_env(char **content, t_env_ms **env_ll)
{
	t_env_ms	**tmp_env;

	tmp_env = env_ll;
	if (get_nb_args(content) == 0)
	{
		print_initialized_environment(*tmp_env);
		set_exit_code(*env_ll, 0);
	}
	else
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		set_exit_code(*env_ll, 1);
	}
	return (env_ll);
}
