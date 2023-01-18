/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_dollar_in_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:08:52 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:53 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
