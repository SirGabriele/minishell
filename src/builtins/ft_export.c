#include "../../includes/minishell.h"

static void	print_all_environment(t_env_ms *env_ll)//ca ne trie qu'avec la premier lettre
{
	t_env_ms	*tmp_env;
	char		letter;

	letter = 'A';
	while (letter)
	{
		tmp_env = env_ll;
		while (tmp_env)
		{
			if (tmp_env->key[0] == letter)
			{
				ft_printf_fd(1, "declare -x %s", tmp_env->key);
				if (tmp_env->value)
					ft_printf_fd(1, "=\"%s\"", tmp_env->value);
				write(1, "\n", 1);
			}
			tmp_env = tmp_env->next;
		}
		if (letter == 'Z')
			letter = '`';
		else if (letter == 'z')
			letter = '^';
		letter++;
	}
}

int	ft_export(char **content, t_env_ms **env_ll)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (!content[1])
	{
		print_all_environment(*env_ll);
		set_exit_code(*env_ll, 0);
		return (0);
	}
	while (content[i] != NULL)
	{
		if (check_errors_env_format(content[i]) == 1)
		{
			ret = 1;
			set_exit_code(*env_ll, 1);
		}
		*env_ll = set_values_export(content[i], *env_ll);
		if (*env_ll == NULL)
		{
			ft_putstr_fd("Error occured in ft_export.c\n", 2);
			set_exit_code(*env_ll, 1);
			return (1);
		}
		i++;
	}
	return (ret);
}
