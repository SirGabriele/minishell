#include "../../includes/minishell.h"

int	is_dollar_inside_quotes(char *content, int i)
{
	int	j;
	int	k;

	j = 0;
	while (content[j])
	{
		if (j == i)
			return (0);
		else if (content[j] == '\'' || content[j] == '\"')
		{
			k = j;
			j++;
			while (content[j] != content[k] && content[j])
				j++;
			if (content[j] == content[k] && j > i)
				return (1);
		}
		j++;
	}
	return (0);
}
