#include "../../includes/minishell.h"

static void	edit_command_status(t_env_ms *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "?"))
			env->value[0] = '0';
		env = env->next;
	}
}

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
	edit_command_status(env);
}
