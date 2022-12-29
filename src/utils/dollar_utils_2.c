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

int	examine_dollar_conditions(char *content, int i)
{
	if (ft_isspace(content[i + 1]))
		return (1);
	if (content[i + 1] == '$')
		return (1);
	if (content[i + 1] == '\0')
		return (1);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
			&& is_it_a_closed_quotes(content + i + 2, content[i + 1]))
		return (1);
	if (ft_isdigit(content[i + 1]))
		return (2);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
			&& !is_it_a_closed_quotes(content + i + 2, content[i + 1])
			&& !is_dollar_inside_quotes(content, i))
		return (3);
	return (0);
}

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
