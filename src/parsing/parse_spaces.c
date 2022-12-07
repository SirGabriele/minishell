#include "../../includes/minishell.h"

static int	length_without_spaces(char *pipeline)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ft_isspace(pipeline[i]) && pipeline[i])
		i++;
	len = i;
	while (pipeline[i])
		i++;
	while (ft_isspace(pipeline[i - 1]) && i)
		i--;
	len = i - len;
	return (len);
}

char	*parse_spaces(char *pipeline)
{
	char	*dst;
	int		i;
	int		j;
	int		len_without_spaces;

	i = 0;
	j = 0;
	len_without_spaces = length_without_spaces(pipeline);
	dst = malloc((len_without_spaces + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (ft_isspace(pipeline[i]) && pipeline[i])
		i++;
	ft_strncpy(dst, pipeline + i, len_without_spaces);
	free(pipeline);
	pipeline = NULL;
	return (dst);
}
