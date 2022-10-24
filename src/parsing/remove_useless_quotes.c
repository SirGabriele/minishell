#include "../../minishell.h"

char	*remove_useless_quotes(char *pipeline)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(characters_without_quotes(pipeline) * sizeof(char));
	while (pipeline[i])
	{
		if (pipeline[i] == ' ' && what_is_character_in(pipeline, i) == 2)
			break ;
		if (pipeline[i] == '\'' || pipeline[i] == '\"')
		{
			tmp = copy_between_quotes(pipeline, i);
			i = get_new_index(pipeline, i);
		}
		else
		{
			tmp = copy_out_of_quotes(pipeline, i);
			i = get_new_index(pipeline, i);
		}
	}

}
