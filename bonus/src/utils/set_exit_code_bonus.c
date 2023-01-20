/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_code_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:10:04 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:10:08 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	set_exit_code(t_env_ms *env_ll, int exit_code)
{
	t_env_ms	*cursor;

	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->key, "?", 1) == 0)
		{
			free(cursor->value);
			cursor->value = ft_itoa(exit_code);
		}
		cursor = cursor->next;
	}
}

int	get_exit_code(t_env_ms *env_ll)
{
	t_env_ms	*cursor;

	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->key, "?", 1) == 0)
		{
			return (ft_atoi(cursor->value));
		}
		cursor = cursor->next;
	}
	return (0);
}
