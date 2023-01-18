#include "../../includes/minishell.h"

void	print_checking_error_msg(char *msg)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", msg);
}
