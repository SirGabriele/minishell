/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_delimiter_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:08:38 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:39 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	get_index_delimiter(const char *user_input, char *delim[10], int index)
{
	int	i;
	int	length_delim;

	i = 0;
	while (delim[i] != NULL)
	{
		length_delim = ft_strlen(delim[i]);
		if (ft_strncmp(user_input + index, delim[i], length_delim) == 0
			&& !what_is_index_in(user_input, index))
			return (i);
		i++;
	}
	return (-1);
}
