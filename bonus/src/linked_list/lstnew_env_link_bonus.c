/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_env_link_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:13:12 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:13:13 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_env_ms	*lstnew_env_link(void)
{
	t_env_ms	*env_link;

	env_link = malloc(sizeof(t_env_ms));
	if (!env_link)
	{
		perror(NULL);
		return (NULL);
	}
	env_link->key = NULL;
	env_link->value = NULL;
	env_link->next = NULL;
	return (env_link);
}
