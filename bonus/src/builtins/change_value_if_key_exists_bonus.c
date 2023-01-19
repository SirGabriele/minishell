/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value_if_key_exists_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:46:43 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:46:45 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	get_delim_symbol_index(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

static int	modify_value(char *content, t_env_ms *link_to_modify)
{
	free(link_to_modify->value);
	link_to_modify->value = ft_strdup(content);
	if (!link_to_modify->value)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

static int	append_value(char *content, t_env_ms *link_to_modify)
{
	link_to_modify->value = ft_strjoin_free_first(link_to_modify->value,
			content);
	if (!link_to_modify->value)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

int	change_value(char *content, t_env_ms *link_to_modify)
{
	int	index_equals_or_plus;
	int	ret;

	ret = 0;
	index_equals_or_plus = get_delim_symbol_index(content);
	if (!ft_strncmp(link_to_modify->key, content, index_equals_or_plus))
	{
		if (content[index_equals_or_plus] == '+')
			ret = append_value(content + index_equals_or_plus + 2,
					link_to_modify);
		else if (content[index_equals_or_plus] == '=')
			ret = modify_value(content + index_equals_or_plus + 1,
					link_to_modify);
	}
	return (ret);
}
