#include "../../includes/minishell.h"

static int	how_many_and_or_operator(const char *user_input)
{
	int	i;
	int nb_and_or_operators;

	i = 0;
	nb_and_or_operators = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '&' && user_input[i + 1] == '&')
			|| (user_input[i] == '|' && user_input[i + 1] == '|'))
			nb_and_or_operators++;
		i++;
	}
	nb_and_or_operators++;
	ft_printf("%d\n", nb_and_or_operators);
	return (nb_and_or_operators);
}

int	init_struct_array(const char *user_input)
{
	t_pipelines_ms	*pipelines;

	pipelines = malloc(sizeof(t_pipelines_ms) * (how_many_and_or_operator(user_input) + 1));
	if (pipelines == NULL)
		return (-1);
	return (0);
}
