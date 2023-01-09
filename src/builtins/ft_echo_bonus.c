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

int	ft_echo(char **content, t_env_ms **env_ll, char *outfile, t_enum_token outfile_mode)
{
	char	*final_string;
	int	i;
	int	options;
	(void)outfile;
	(void)outfile_mode;

	final_string = NULL;
	i = 0;
	options = get_nb_options(content + 1);
	while (content[1 + i + options])
	{
/*		while (content[1 + i + options] &&
			(ft_strcmp("(", content[1 + i + options]) == 0
			|| ft_strcmp(")", content[1 + i + options]) == 0))
			i++;*/
		if (!content[1 + i + options])
			break ;
		final_string = ft_strjoin_free_first(final_string, content[1 + i + options]);
		if (content[1 + i + options + 1])
			final_string = ft_strjoin_free_first(final_string, " ");
		i++;
	}
	if (final_string)
	{
		ft_printf_fd(1, "%s", final_string);
		free(final_string);
	}
	if (!options)
		write(1, "\n", 1);
	set_exit_code(*env_ll, 0);
	return (0);
}
