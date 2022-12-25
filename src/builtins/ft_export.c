#include "../../includes/minishell.h"

static void	print_all_environment(t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		ft_printf_fd(0, "declare -x %s=\"", tmp_env->key);
		ft_printf_fd(0, "%s\"\n", tmp_env->value);
		tmp_env = tmp_env->next;
	}
}

void	ft_export(char **content, t_env_ms *env)
{
	if (!*content)
		print_all_environment(env);
	else if (check_errors_env_format(content))
		return ;
	else
		env = set_values_export(content, env);
}
