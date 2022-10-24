#include "../../minishell.h"

t_cmd_ms	*parsing(t_cmd_ms *commands, int len_commands)
{
	int	i;

	i = 0;
	while (i < len_commands)
	{
		commands[i].pipeline = remove_useless_spaces(commands[i].pipeline);
		commands[i].pipeline = remove_useless_quotes(commands[i].pipeline);
		commands = identify_command_structure(commands);
	}
	return (commands);
}
