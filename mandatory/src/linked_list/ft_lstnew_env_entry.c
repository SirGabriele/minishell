/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env_entry.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:40:53 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:40:53 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_len_key(const char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	return (i);
}

static int	get_len_value(const char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	i++;
	while (env[i + j] != '\0')
		j++;
	return (j);
}

static char	*get_env_value(const char *env)
{
	char	*value;
	int		len_value;

	len_value = get_len_value(env);
	value = malloc(sizeof(char) * (len_value + 1));
	if (value == NULL)
		return (NULL);
	value = ft_strncpy(value, (char *)env + get_len_key(env) + 1, len_value);
	return (value);
}

static char	*get_env_key(const char *env)
{
	char	*key;
	int		len_key;

	len_key = get_len_key(env);
	key = malloc(sizeof(char) * (len_key + 1));
	if (key == NULL)
		return (NULL);
	key = ft_strncpy(key, (char *)env, len_key);
	return (key);
}

t_env_ms	*ft_lstnew_env_entry(const char *env)
{
	t_env_ms	*elem;

	elem = malloc(sizeof(t_env_ms));
	if (elem == NULL)
		return (NULL);
	elem->key = get_env_key(env);
	if (ft_strlen(elem->key) == ft_strlen(env))
	{
		elem->value = malloc(sizeof(char) * 1);
		elem->value[0] = '\0';
	}
	else
		elem->value = get_env_value(env);
	if (elem->key == NULL || elem->value == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
