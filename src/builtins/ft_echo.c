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

int	ft_echo(char **content)
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
	return (0);
}
