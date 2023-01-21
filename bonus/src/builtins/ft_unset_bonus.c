/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:49 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/21 01:03:09 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	delete_next_link(t_env_ms *env, char *content)
{
	t_env_ms	*tmp;

	if (ft_strcmp(content, env->next->key) == 0)
	{
		tmp = env->next->next;
		free(env->next->key);
		free(env->next->value);
		free(env->next);
		env->next = tmp;
		return (0);
	}
	return (1);
}

static void	deletion_process(t_env_ms **env, char *content)
{
	int	ret;

	while ((*env)->next)
	{
		ret = delete_next_link(*env, content);
		if (ret == 0)
			break ;
		if ((*env)->next)
			*env = (*env)->next;
	}
}

int	ft_unset(char **content, t_env_ms **env)
{
	t_env_ms	*env_head;
	int			i;
	int			ret;

	ret = 0;
	i = 0;
	env_head = *env;
	while (content[i])
	{
		deletion_process(env, content[i]);
		*env = env_head;
		i++;
	}
	return (ret);
}
