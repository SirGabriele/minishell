/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_a_closed_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:37 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:46:37 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
