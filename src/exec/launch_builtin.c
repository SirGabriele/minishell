#include "../../includes/minishell.h"

/*int	is_a_builtin(char *content)
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
}*/

int	is_cd_or_exit(char *content)//ajouter verif redirection. cd Desktop > out < infile
{
	if (!ft_strcmp(content, "cd"))
		return (0);
//	else if (!ft_strcmp(content[0], "exit"))
//		return (0);
	return (1);
}

int	is_a_builtin(char *content)
{
	if (!ft_strcmp(content, "echo")
		|| !ft_strcmp(content, "cd")
		|| !ft_strcmp(content, "pwd")
		|| !ft_strcmp(content, "export")
		|| !ft_strcmp(content, "unset")
		|| !ft_strcmp(content, "env")
		|| !ft_strcmp(content, "exit"))
		return (0);
	return (1);
}

/*int	is_a_builtin(t_node_ms *node, t_env_ms *env_ll)//ajouter verif redirection. cd Desktop > out < infile
{
	int	ret;

	ret = 0;
//	if (!ft_strcmp(content[0], "echo"))
//		ret = ft_echo(node, env_ll);
	else if (!ft_strcmp(content[0], "cd"))
		ret = ft_cd(node, env_ll);
//	else if (!ft_strcmp(content[0], "pwd"))
		ret = ft_pwd(node, env_ll);
	else if (!ft_strcmp(content[0], "export"))
		ret = ft_export(node, env_ll);
	else if (!ft_strcmp(content[0], "unset"))
		ret = ft_unset(node, env_ll);
	else if (!ft_strcmp(content[0], "env"))
		ret = ft_env(node, env_ll);//
	//else if (!ft_strcmp(content[0], "exit"))
	//	env_ll = ft_exit(content + 1);
	return (ret);
}*/

int	simple_cd_or_exit(char **content, t_env_ms *env_ll)
{
	int	ret;
	
	ret = 0;
	if (!ft_strcmp(content[0], "cd"))
		ret = ft_cd(content + 1, env_ll);
	//else if (!ft_strcmp(content[0], "exit"))
	//	env_ll = ft_exit(content + 1);
	return (ret);
}
