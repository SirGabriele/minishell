#include "../../includes/minishell_bonus.h"

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

static void	print_string(char *final_string, char *outfile,
	t_enum_token outfile_mode)
{
	int	fd;

	if (outfile == NULL || outfile_mode == TOK_NULL || outfile_mode == TOK_PIPE)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	if (final_string)
		ft_printf_fd(fd, "%s", final_string);
	if (outfile != NULL)
		close(fd);
}

int	ft_echo(t_node_ms *node)
{
	char	*final_string;
	int		i;
	int		options;

	final_string = NULL;
	i = 0;
	options = get_nb_options(node->content + 1);
	while (node->content[1 + i + options])
	{
		if (!node->content[1 + i + options])
			break ;
		final_string = ft_strjoin_free_first(final_string,
				node->content[1 + i + options]);
		if (node->content[1 + i + options + 1])
			final_string = ft_strjoin_free_first(final_string, " ");
		i++;
	}
	if (!options)
		final_string = ft_strjoin_free_first(final_string, "\n");
	print_string(final_string, node->outfile, node->outfile_mode);
	free(final_string);
	return (0);
}
