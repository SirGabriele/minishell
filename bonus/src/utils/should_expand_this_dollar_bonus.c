/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_expand_this_dollar_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:06:22 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:06:22 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	should_expand_this_dollar(char *content, int index)
{
	int		i;
	char	c;

	i = 0;
	while (content[i] != '\0' && i != index)
	{
		if (content[i] == '\"' || content[i] == '\'')
		{
			c = content[i];
			while (content[i] != c)
			{
				if (i == index && c == '\"')
					return (0);
				else if (i == index && c == '\'')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}
