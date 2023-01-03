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

int	ft_echo(t_node_ms *node, t_env_ms *env_ll)
{
	int	i;
	int	options;

	i = 0;
	options = get_nb_options(node->content + 1);
	while (node->content[1 + i + options])
	{
		ft_printf("%s", node->content[1 + i + options]);
		if (node->content[1 + i + options + 1])
			write(1, " ", 1);
		i++;
	}
	if (!options)
		write(1, "\n", 1);
	set_exit_code(env_ll, 0);
	return (0);
//	edit_command_status(env);
}
