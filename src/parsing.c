/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:33:12 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/04 11:05:30 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_parsed(char *line_read)
{
	char	*duplicate;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = NULL;
	duplicate = NULL;
	while (line_read[i])
	{
		if (line_read[i] == 39 || line_read[i] == 34)
		{
			j = i++;
			while (line_read[i] != line_read[j] && line_read[i])
				i++;
			if (!line_read[i])
			{
				ft_printf("Missing quotes.\n");
				return (NULL);
			}
			if (i - j != 1)
			{
				tmp = malloc((i - j) * sizeof(char));
				if (!tmp)
					return (NULL);
				tmp = ft_strncpy(tmp, line_read + j + 1, i - j - 1);
				duplicate = ft_strjoin(duplicate, tmp);
				if (!duplicate)
					return (NULL);
			}
		}
		else
		{
			tmp = ft_strncpy(tmp, line_read + i, 1);
			duplicate = ft_strjoin(duplicate, tmp);
		}
		i++;
	}
	return (duplicate);
}
