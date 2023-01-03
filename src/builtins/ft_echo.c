#include "../../includes/minishell.h"

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

int	ft_echo(char **content, t_env_ms *env_ll)
{
	int	i;
	int	options;

	i = 0;
	options = get_nb_options(content + 1);
	while (content[1 + i + options])
	{
		ft_printf("%s", content[1 + i + options]);
		if (content[1 + i + options + 1])
			write(1, " ", 1);
		i++;
	}
	if (!options)
		write(1, "\n", 1);
	set_exit_code(env_ll, 0);
	return (0);
}
