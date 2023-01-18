#include "../../includes/minishell_bonus.h"

int	get_nb_dollars(char *unparsed, int i)
{
	int	nb_dollars;
	int	j;

	nb_dollars = 0;
	j = 0;
	while (unparsed[j])
	{
		if (unparsed[j] == '$')
			nb_dollars++;
		if (j == i)
			return (nb_dollars);
		j++;
	}
	return (nb_dollars);
}
