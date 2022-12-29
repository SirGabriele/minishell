#include "../../includes/minishell.h"

int	is_a_builtin(char *content)
{
	if (!ft_strcmp(content, "echo"))
		return (0);
	if (!ft_strcmp(content, "cd"))
		return (0);
	if (!ft_strcmp(content, "pwd"))
		return (0);
	if (!ft_strcmp(content, "export"))
		return (0);
	if (!ft_strcmp(content, "unset"))
		return (0);
	if (!ft_strcmp(content, "env"))
		return (0);
	if (!ft_strcmp(content, "exit"))
		return (0);
	return (1);
}

void	launch_builtin(char **content, t_env_ms *env_ll)
{
	if (!ft_strcmp(content[0], "echo"))
		ft_echo(content + 1, env_ll);
	else if (!ft_strcmp(content[0], "cd"))
		ft_cd(content + 1, env_ll);
	else if (!ft_strcmp(content[0], "pwd"))
		ft_pwd(env_ll);
	else if (!ft_strcmp(content[0], "export"))
		ft_export(content + 1, env_ll);
	else if (!ft_strcmp(content[0], "unset"))
		ft_unset(content + 1, env_ll);
	else if (!ft_strcmp(content[0], "env"))
		ft_env(content + 1, env_ll);
	//else if (!ft_strcmp(content[0], "exit"))
	//	env_ll = ft_exit(content + 1);
}
