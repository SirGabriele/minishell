#include "../../includes/minishell.h"

void	ft_pwd(t_env_ms *env)
{
	char	*pwd;

	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror(NULL);
	ft_printf_fd(0, "%s\n", pwd);
}
