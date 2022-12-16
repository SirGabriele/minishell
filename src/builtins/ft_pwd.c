#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror(NULL);
	ft_printf_fd(0, "%s\n", pwd);
	return (0);
}
