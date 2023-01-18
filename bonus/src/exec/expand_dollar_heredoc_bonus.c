/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_heredoc_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:43:59 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:51:47 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	get_len_key(char *user_input, int index)
{
	int	len_after_dollar;

	len_after_dollar = 0;
	while (ft_isalnum(user_input[index + len_after_dollar + 1]) == 1
		&& user_input[index + len_after_dollar + 1] != '\0')
		len_after_dollar++;
	return (len_after_dollar);
}

static char	*get_env_value(char *user_input, int len_after_dollar,
	t_env_ms *env_ll)
{
	t_env_ms	*env_cpy;
	char		*key;

	key = NULL;
	key = malloc(sizeof(char) * (len_after_dollar + 1));
	if (key == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	key = ft_strncpy(key, user_input, len_after_dollar);
	env_cpy = env_ll;
	while (env_cpy != NULL)
	{
		if (ft_strcmp(env_cpy->key, key) == 0)
		{
			free(key);
			return (env_cpy->value);
		}
		env_cpy = env_cpy->next;
	}
	free(key);
	return (NULL);
}

void	expand_dollar_heredoc(char *user_input, t_pipes_ms *pipes,
	t_env_ms *env_ll)
{
	char	*env_value;
	int		i;
	int		len_aftr_dol;

	i = 0;
	while (user_input[i] != '\0')
	{
		len_aftr_dol = 0;
		if (user_input[i] == '$')
		{
			len_aftr_dol = get_len_key(user_input, i);
			if (len_aftr_dol == 0)
				write(pipes->before[1], "$", 1);
			env_value = get_env_value(user_input + i + 1, len_aftr_dol, env_ll);
			if (env_value != NULL)
				ft_putstr_fd(env_value, pipes->before[1]);
			else
				write(pipes->before[1], "", 1);
			i += len_aftr_dol;
		}
		else
			write(pipes->before[1], &user_input[i], 1);
		i++;
	}
	write(pipes->before[1], "\n", 1);
}
