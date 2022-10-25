#include "../../minishell.h"

int	get_number_of_arguments(char *pipeline)
{
	int	i;
	int	nb_arguments;

	i = 0;
	j = 1;
	while (pipeline[i])
	{
		if (pipeline[i] == ' ' && !what_is_character_in(pipeline, i))
			nb_arguments++;
		i++;
	}
	return (nb_arguments);
}

int	get_end_of_argument_index(char *pipeline)
{
	int	i;

	i = 0;
	while (pipeline[i])
	{
		if (pipeline[i] == ' ' && !what_is_character_in(pipeline, i))
			return (i);
		i++;
	}
	return (i);
}

t_cmd_ms	*parse_command_line(char *pipeline)
{
	char	*arg;
	int		nb_arguments;

	pipeline = remove_useless_spaces(pipeline);
	nb_arguments = get_number_of_arguments(pipeline)
	while (nb_arguments)
	{
		arg = malloc(get_end_of_argument_index(pipeline) * sizeof(char));
		arg = ft_strncpy(tmp, pipeline, get_end_of_argument_index(pipeline));
		arg = parse_argument(arg);
		free(arg);
	}
	return ();
}
