/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_content_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:50:23 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 23:37:11 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*get_new_content(char *parsed, char *key, char *value, int nb_dollars)
{
	char	*new_parsed;
	int		key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (parsed[i])
	{
		if (parsed[i] == '$')
			nb_dollars--;
		if (parsed[i] == '$' && !nb_dollars)
		{
			new_parsed = join_and_manage_dollar(parsed, value, key_len, i);
			return (new_parsed);
		}
		i++;
	}
	return (parsed);
}
