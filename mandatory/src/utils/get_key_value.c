/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:18 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:18 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
