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

void	ft_cd(char **content, t_env_ms *env)
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
		ft_putstr_fd("minishell: cd: missing relative/absolute path\n", 2);
	else
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	set_exit_code(env, 0);
//	edit_command_status(env);
}
