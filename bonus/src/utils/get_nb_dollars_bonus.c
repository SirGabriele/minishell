/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_dollars_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:08:56 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:57 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
