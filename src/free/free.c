#include "../../includes/minishell.h"

void	free_commands(t_cmd_ms *commands, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(commands[j].pipeline);
		j++;
	}
	free(commands);
}
