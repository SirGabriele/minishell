/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dollar_underscore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:24 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:25 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_dollar_underscore(t_env_ms *env_ll, char **content)
{
	t_env_ms	*cursor;
	int			i;

	i = 0;
	if (!content || !content[i])
		return ;
	while (content && content[i] != NULL)
		i++;
	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->key, "_", 1) == 0)
		{
			free(cursor->value);
			cursor->value = ft_strdup(content[i - 1]);
		}
		cursor = cursor->next;
	}
}
