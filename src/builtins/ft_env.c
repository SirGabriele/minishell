#include "../../includes/minishell.h"

static void	edit_command_status(t_env_ms *env, char exit_status)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "?"))
			tmp_env->value[0] = exit_status;
		tmp_env = tmp_env->next;
	}
}

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

t_env_ms	*ft_env(char **content, t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	if (get_nb_args(content) == 0)
	{
		print_initialized_environment(tmp_env);
		edit_command_status(env, '0');
	}
	else
	{
		ft_printf_fd(2, "minishell: env: too many arguments\n");
		edit_command_status(env, '1');
	}
	return (env);
}
