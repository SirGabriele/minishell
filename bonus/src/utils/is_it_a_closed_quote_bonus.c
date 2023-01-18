/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_a_closed_quote_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:29 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:09:30 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
