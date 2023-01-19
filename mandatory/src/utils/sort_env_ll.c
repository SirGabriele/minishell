/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_ll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:31 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:31 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
