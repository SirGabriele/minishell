#include "../includes/minishell.h"

int	launch_program(char *user_input)
{
	if (ft_check_quotes(user_input) == -1)
		return (-1);
	if (init_struct_array(user_input) == -1)
		return (-1);
	return (0);
}
