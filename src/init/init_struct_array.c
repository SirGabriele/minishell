#include "../../includes/minishell.h"

int	count_pipes(const char *user_input)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = 0;
	while (user_input[i])
	{
		if (what_is_character_in(user_input, i) == 2  && user_input[i] == '|')
			nb_pipes++;
		i++;
	}
	return (nb_pipes);
}

t_cmd_ms	*init_struct_array(const char *user_input)
{
	t_cmd_ms	*commands;
	char		**commands_splited;
	int			i;

	i = 0;
	commands = malloc((count_pipes(user_input) + 1) * sizeof(t_cmd_ms));
	commands_splited = ft_split(user_input, '|');
	if (commands == NULL)
		return (NULL);
	else if (commands_splited == NULL)
		return (NULL);
	while (i <= count_pipes(user_input))
	{
		commands[i].pipeline = ft_strjoin(NULL, commands_splited[i]);
		if (!commands[i].pipeline)
		{
			free_commands(commands, i);
			return (NULL);
		}
		ft_printf("'%s'\n", commands[i].pipeline);
		free(commands_splited[i]);
		i++;
	}
	free(commands_splited);
	return (commands);
}
