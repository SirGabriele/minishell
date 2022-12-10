#include "../includes/minishell.h"

int	check_nb_commands(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (!ft_isspace(user_input[i]))
			return (1);
		i++;
	}
	return (0);
}
