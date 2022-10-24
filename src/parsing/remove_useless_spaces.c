#include "../../minishell.h"

static int	len_without_spaces(char *pipeline)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipeline[j] && pipeline[j] == ' ')
		j++;
	while (pipeline[i + j])
		i++;
	while (pipeline[i + j - 1] == ' ' && i)
		i--;
	return (i);
}

char	*remove_useless_spaces(char	*pipeline)
{
	char	*new_pipeline;
	int		i;

	i = 0;
	new_pipeline = malloc((len_without_spaces + 1) * sizeof(char));
	if (!new_pipeline)
		return (NULL);
	while (*pipeline == ' ' && *pipeline)
		pipeline++;
	new_pipeline = ft_strncpy(pipeline, len_without_spaces(pipeline));
	return (new_pipeline);
}
