#include "../../includes/minishell.h"

static int	count_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}

static void	identify_error(char *content)//EFAULT EIO ELOOP
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", content);
	if (!error)
		perror(NULL);
	perror(error);
	free(error);
}

int	ft_cd(char **content)
{
	int	exit_status;
	int	nb_args;

	exit_status = 1;
	nb_args = count_args(content);
	if (nb_args == 1)
	{
		exit_status = chdir(content[0]);
		if (exit_status)
			identify_error(*content);
	}
	else if (!nb_args)
		ft_printf_fd(2, "minishell: cd: missing relative/absolute path\n");
	else
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	return (exit_status);
}
