#include "../../includes/minishell.h"

static int	get_nb_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}

static void	print_environment_variables(t_env_ms *env_ll, char *outfile,
	t_enum_token outfile_mode)
{
	int	fd;

	if (outfile == NULL || outfile_mode == TOK_PIPE || outfile_mode == TOK_NULL)
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

int	ft_env(char **content, t_env_ms *env_ll, char *outfile,
	t_enum_token outfile_mode)
{
	int			ret;

	ret = 0;
	if (get_nb_args(content) == 0)
		print_environment_variables(env_ll, outfile, outfile_mode);
	else
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		ret = 1;
	}
	return (ret);
}
