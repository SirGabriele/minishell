/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:21 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:22 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
