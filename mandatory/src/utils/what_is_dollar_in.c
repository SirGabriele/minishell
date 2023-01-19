/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_dollar_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:38 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:39 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	what_is_dollar_in(const char *parsed, int i)
{
	int		j;
	char	c;

	j = 0;
	while (parsed[j] != '\0')
	{
		if (parsed[j] == '\"' || parsed[j] == '\'')
		{
			c = parsed[j];
			j++;
			while (parsed[j] != c && parsed[j] != '\0')
				j++;
			if (j > i && c == '\"')
				return (0);
			else if (j > i && c == '\'')
				return (-1);
		}
		else if (parsed[j] == '$')
			return (0);
		j++;
	}
	return (-1);
}
