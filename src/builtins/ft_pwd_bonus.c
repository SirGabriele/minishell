#include "../../includes/minishell.h"

int	ft_pwd(t_env_ms **env, char *outfile, t_enum_token outfile_mode)
{
	char	*pwd;
	(void)outfile;
	(void)outfile_mode;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror(NULL);
	ft_printf_fd(1, "%s\n", pwd);
	set_exit_code(*env, 0);
	return (0);
}
