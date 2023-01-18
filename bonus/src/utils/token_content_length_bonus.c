/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_content_length_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:10:00 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:10:01 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	token_content_length(char *user_input, char *delim[10])
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
