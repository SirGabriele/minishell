#include "../../includes/minishell.h"

static void	change_pwd_and_oldpwd(t_env_ms *env_ll)
{
	t_env_ms	*old_pwd;
	t_env_ms	*pwd;
	char		*post_cd_pwd;

	while (env_ll != NULL)
	{
		if (ft_strcmp(env_ll->key, "OLDPWD") == 0)
			old_pwd = env_ll;
		else if (ft_strcmp(env_ll->key, "PWD") == 0)
			pwd = env_ll;
		env_ll = env_ll->next;
	}
	post_cd_pwd = getcwd(NULL, 0);
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = post_cd_pwd;
}

static int	change_directory(char *content, t_env_ms *env_ll)
{
	char	*error;
	int		exit_status;

	error = ft_strjoin("minishell: cd: ", content);
	if (!error)
		perror(NULL);
	exit_status = chdir(content);
	if (exit_status)
	{
		perror(error);
		free(error);
		return (1);
	}
	change_pwd_and_oldpwd(env_ll);
	free(error);
	return (0);
}

int	ft_cd(char **content, t_env_ms *env_ll)
{
	int	nb_args;
	int	ret;

	ret = 0;
	nb_args = count_args(content);
	if (nb_args == 1)
		ret = change_directory(content[0], env_ll);
	else
	{
		if (!nb_args)
			ft_putstr_fd("minishell: cd: missing relative/absolute path\n", 2);
		else
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (ret);
}
