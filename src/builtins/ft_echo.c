#include "../../includes/minishell.h"

/*static void	edit_command_status(t_env_ms *env)
{
	t_env_ms	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "?"))
			tmp_env->value[0] = '0';
		tmp_env = tmp_env->next;
	}
}*/

static int	is_option(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-')
	{
		i++;
		while (content[i])
		{
			if (content[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

static int	get_nb_options(char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (is_option(content[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

void	ft_echo(char **content, t_env_ms *env)
{
	int	i;
	int	options;

	i = 0;
	options = get_nb_options(content);
	while (content[i + options])
	{
		ft_printf("%s", content[i + options]);
		if (content[i + options + 1])
			ft_printf(" ");
		i++;
	}
	if (!options)
		ft_printf("\n");
	set_exit_code(env, 0);
//	edit_command_status(env);
}
