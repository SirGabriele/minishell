#include "../../minishell.h"

t_cmd_ms	*parsing(t_cmd_ms *commands, int len_commands)
{
	int	i;

	i = 0;
	while (i < len_commands)
		commands = parse_command_line(commands[i].pipeline);
	return (commands);
}
