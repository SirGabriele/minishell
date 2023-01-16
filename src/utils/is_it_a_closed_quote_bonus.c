#include "../../includes/minishell.h"

int	is_it_a_closed_quote(char *content, char quote)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == quote)
		{
			if ((quote == '\'' && what_is_dollar_in(content, i))
				|| (quote == '\"' && !what_is_dollar_in(content, i)))

				quotes++;
		}
		i++;
	}
	if (!(quotes % 2))
		return (1);
	return (0);
}
