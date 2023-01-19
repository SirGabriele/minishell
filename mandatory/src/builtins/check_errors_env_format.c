/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_env_format.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:38:17 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:38:18 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_key_format(char *content)
{
	if (!ft_isalpha(content[0]) && content[0] != '_')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	check_spaces_after_key(char *content)
{
	int	i;

	i = 1;
	if (content[0] == '=')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content + i, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (content[i])
	{
		if (content[i] == '=' && ft_isspace(content[i - 1]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(content + i, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		else if (content[i] == '=' && !ft_isspace(content[i - 1]))
			return (0);
		i++;
	}
	return (0);
}

int	check_errors_env_format(char *content)
{
	int	error;

	error = 0;
	if (check_key_format(content) == 1)
		error = 1;
	if (content[0] != '=' && check_spaces_after_key(content) == 1)
		error = 1;
	return (error);
}
