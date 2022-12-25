#include "../../includes/minishell.h"

int	is_it_a_closed_quotes(char *content, char quote)
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

int	examine_dollar_conditions(char *content, int i)
{
	if (content[i + 1] == ' ')
		return (1);
	if (content[i + 1] == '$')
		return (1);
	if (content[i + 1] == '\0')
		return (1);
	if (i > 0 && content[i - 1] == '\"' && content[i + 1] == '\"')
		return (1);
	if (ft_isdigit(content[i + 1]))
		return (2);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
			&& !is_it_a_closed_quotes(content + i + 2, content[i + 1]))
		return (3);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
			&& is_it_a_closed_quotes(content + i + 2, content[i + 1]))
		return (4);
	return (0);
}

int	get_diff_nb_dollars(char *old_parsed, char *parsed)
{
	int	i;
	int	nb_dollars;

	i = 0;
	nb_dollars = 0;
	while (old_parsed[i])
	{
		if (old_parsed[i] == '$')
			nb_dollars++;
		i++;
	}
	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '$')
			nb_dollars--;
		i++;
	}
	return (nb_dollars);
}
