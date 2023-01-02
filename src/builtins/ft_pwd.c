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

void	ft_pwd(t_env_ms *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror(NULL);
	ft_printf_fd(0, "%s\n", pwd);
	set_exit_code(env, 0);
//	edit_command_status(env);
}
