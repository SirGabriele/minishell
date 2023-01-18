/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dollar_underscore_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:50 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:09:50 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
