#include "../../includes/minishell_bonus.h"

int	ft_pwd(char *outfile, t_enum_token outfile_mode)
{
	char	*pwd;
	int		fd;

	if (outfile == NULL || outfile_mode == TOK_NULL || outfile_mode == TOK_PIPE)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror(NULL);
		return (1);
	}
	else
	{
		ft_printf_fd(fd, "%s\n", pwd);
		free(pwd);
	}
	if (outfile != NULL)
		close(fd);
	return (0);
}
