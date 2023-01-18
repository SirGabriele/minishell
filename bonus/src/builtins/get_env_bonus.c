/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:48:02 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:48:02 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	create_key_and_value(t_env_ms *env_link, char *content,
	int index_delim)
{
	env_link->key = ft_strndup(content, index_delim);
	if (!env_link->key)
	{
		free(env_link);
		return (-1);
	}
	env_link->value = ft_strdup(content + index_delim + 1);
	if (!env_link->value)
	{
		free(env_link->key);
		env_link->key = NULL;
		return (-1);
	}
	return (0);
}

static int	create_key(t_env_ms *env_link, char *content)
{
	env_link->key = ft_strndup(content, ft_strlen(content));
	if (!env_link->key)
		return (-1);
	env_link->value = NULL;
	return (0);
}

static int	get_delim_sign_index(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			return (i);
		i++;
	}
	return (0);
}

t_env_ms	*get_env(char *content)
{
	t_env_ms	*env_link;
	int			index_delim;

	env_link = lstnew_env_link();
	if (!env_link)
		return (NULL);
	index_delim = get_delim_sign_index(content);
	if (index_delim == 0)
	{
		if (create_key(env_link, content) == -1)
		{
			free(env_link);
			env_link = NULL;
		}
	}
	else
	{
		if (create_key_and_value(env_link, content, index_delim) == -1)
		{
			free(env_link);
			env_link = NULL;
		}
	}
	return (env_link);
}
