/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:49 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:47:49 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	is_invalid_identifier(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '~' || content[i] == '#' || content[i] == ' '
			|| content[i] == '{' || content[i] == '[' || content[i] == '-'
			|| content[i] == '^' || content[i] == '@' || content[i] == ']'
			|| content[i] == '}' || content[i] == '*' || content[i] == '%'
			|| content[i] == '!' || content[i] == ':' || content[i] == '/'
			|| content[i] == '.' || content[i] == '?' || content[i] == ',')
		{
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
				content[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

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
		if (is_invalid_identifier(content[i]) == 1)
		{
			ret = 1;
			i++;
			continue ;
		}
		deletion_process(env, content[i]);
		*env = env_head;
		i++;
	}
	return (ret);
}