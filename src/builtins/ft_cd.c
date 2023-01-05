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
	error = ft_strjoin(error, ":");
	if (!error)
		perror(NULL);
	if (content[0] != '-')
	{
		perror(error);
		set_exit_code(env_ll, 1);
	}
	else
	{
		ft_printf_fd(2, "minishell: cd: %s: invalid option\n", content);
		set_exit_code(env_ll, 2);
	}
	free(error);
}

int	ft_cd(char **content, t_env_ms **env_ll)
{
	int	exit_status;
	int	nb_args;

	nb_args = count_args(content);
	if (nb_args == 1)
	{
		exit_status = chdir(content[0]);
		if (exit_status)
			identify_error(*content, *env_ll);
		else
			set_exit_code(*env_ll, 0);
		return (0);
	}
	else
	{
		if (!nb_args)
			ft_putstr_fd("minishell: cd: missing relative/absolute path\n", 2);
		else
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		set_exit_code(*env_ll, 1);
	}
	return (0);
}
