/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit_value_out_of_range.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:32 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:33 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_smaller_than_llong_min(char *content)
{
	int	res;

	res = ft_strcmp(content, "9223372036854775808");
	if (res > 0)
		return (1);
	return (0);
}

static int	is_bigger_than_llong_max(char *content)
{
	int	res;

	res = ft_strcmp(content, "9223372036854775808");
	if (res >= 0)
		return (1);
	return (0);
}

int	is_exit_value_out_of_range(char *content)
{
	int	len_content;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while (ft_isspace(content[i]) == 1)
		i++;
	if (content[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (content[i] == '+')
		i++;
	len_content = ft_strlen(content + i);
	if (len_content < 19)
		return (0);
	else if (len_content > 19)
		return (1);
	if ((sign == 1 && is_bigger_than_llong_max(content + i) == 1)
		|| (sign == -1 && is_smaller_than_llong_min(content + i) == 1))
		return (1);
	return (0);
}
