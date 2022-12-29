#include "../../includes/minishell.h"

static void	print_all_environment(t_env_ms *env)
{
	t_env_ms	*tmp_env;
	char		letter;

	letter = 'A';
	while (letter)
	{
		tmp_env = env;
		while (tmp_env)
		{
			if (tmp_env->key[0] == letter/* && ft_strcmp(tmp_env->key, "?")*/)
			{
				ft_printf_fd(0, "declare -x %s", tmp_env->key);
				if (tmp_env->value)
					ft_printf_fd(0, "=\"%s\"", tmp_env->value);
				ft_printf_fd(0, "\n");
			}
			tmp_env = tmp_env->next;
		}
		if (letter == 'Z')
			letter = '`';
		else if (letter == 'z')
			letter = '^';
		else if (letter == '_')
			letter = -1;
		letter++;
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
