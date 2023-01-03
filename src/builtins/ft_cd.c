#include "../../includes/minishell.h"

static int	count_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}

static void	identify_error(char *content, t_env_ms *env_ll)//EFAULT EIO ELOOP
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", content);
	if (!error)
		perror(NULL);
	perror(error);
	free(error);
	set_exit_code(env_ll, 1);
}

int	ft_cd(char **content, t_env_ms *env_ll)
{
	int	exit_status;
	int	nb_args;

	exit_status = 1;
	nb_args = count_args(content);
	set_exit_code(env_ll, 1);
	if (nb_args == 1)
	{
		exit_status = chdir(content[0]);
		if (exit_status)
			identify_error(*content, env_ll);
		else
			set_exit_code(env_ll, 0);
		return (0);
	}
	else if (!nb_args)
		ft_putstr_fd("minishell: cd: missing relative/absolute path\n", 2);
	else
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (0);
}
