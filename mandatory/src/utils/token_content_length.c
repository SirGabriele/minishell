/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_content_length.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:34 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:35 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_content_length(char *user_input, char *delim[6])
{
	int	i;
	int	index_delim;

	i = 0;
	while (user_input[i])
	{
		index_delim = get_index_delimiter(user_input, delim, i);
		if (index_delim >= 0 && i)
			return (i);
		else if (index_delim >= 0 && !i)
			return (ft_strlen(delim[index_delim]));
		else if (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			return (i);
		i++;
	}
	return (i);
}
