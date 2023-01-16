#include "../../includes/minishell.h"

int	is_all_digit(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-' || content[i] == '+')
		i++;
	while (content[i] != '\0')
	{
		if (ft_isdigit(content[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}
