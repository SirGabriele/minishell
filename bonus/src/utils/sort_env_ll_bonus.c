/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_ll_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:08:33 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:34 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	sort_env_ll(t_env_ms *env_ll)
{
	t_env_ms	*current;
	t_env_ms	*next;
	char		*temp_key;
	char		*temp_value;

	current = env_ll;
	while (current->next != NULL)
	{
		next = current->next;
		if (ft_strcmp(current->key, next->key) > 0)
		{
			temp_key = next->key;
			temp_value = next->value;
			next->key = current->key;
			next->value = current->value;
			current->key = temp_key;
			current->value = temp_value;
			current = env_ll;
		}
		else
		{
			current = current->next;
			next = current->next;
		}
	}
}
