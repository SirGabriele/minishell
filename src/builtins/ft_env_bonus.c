#include "../../includes/minishell.h"

static void	print_environment_variables(t_env_ms *env_ll, char *outfile,
	t_enum_token outfile_mode)
{
	int	fd;

	if (outfile == NULL || outfile_mode == TOK_NULL || outfile_mode == TOK_PIPE)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	while (env_ll != NULL)
	{
		if (env_ll->key[0] != '?' && env_ll->value != NULL)
		{
			ft_printf_fd(fd, "%s=%s", env_ll->key, env_ll->value);
			write(fd, "\n", 1);
		}
		env_ll = env_ll->next;
	}
	if (outfile != NULL)
		close(fd);
}

int	ft_env(t_node_ms *node, t_env_ms *env_ll)
{
	int			ret;

	ret = 0;
	if (count_args(node->content + 1) == 0)
		print_environment_variables(env_ll, node->outfile, node->outfile_mode);
	else
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		ret = 1;
	}
	return (ret);
}
