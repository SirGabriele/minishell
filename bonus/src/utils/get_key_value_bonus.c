/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_value_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:40 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:07:41 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*get_key_value(t_env_ms *env_ll, char *key)
{
	int		len;

	len = ft_strlen(key);
	while (env_ll)
	{
		if (!ft_strncmp(env_ll->key, key, len)
			&& len && !env_ll->key[len])
			return (env_ll->value);
		env_ll = env_ll->next;
	}
	return (NULL);
}
