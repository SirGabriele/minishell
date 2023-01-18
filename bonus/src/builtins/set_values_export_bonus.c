/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values_export_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:54 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:47:55 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	extend_env_list(char *content, t_env_ms *env_ll)
{
	while (env_ll->next)
		env_ll = env_ll->next;
	env_ll->next = get_env(content);
	if (env_ll->next == NULL)
		return (1);
	return (0);
}

static t_env_ms	*does_key_exist(char *content, t_env_ms *env_ll)
{
	int	len;

	while (env_ll)
	{
		len = ft_strlen(env_ll->key);
		if (!ft_strncmp(content, env_ll->key, len)
			&& (content[len] == '=' || content[len] == '+' || !content[len]))
			return (env_ll);
		env_ll = env_ll->next;
	}
	return (NULL);
}

int	set_values_export(char *content, t_env_ms *env_ll)
{
	t_env_ms	*link_to_modify;
	int			ret;

	ret = 0;
	link_to_modify = does_key_exist(content, env_ll);
	if (link_to_modify != NULL)
		ret = change_value(content, link_to_modify);
	else
		ret = extend_env_list(content, env_ll);
	return (ret);
}
