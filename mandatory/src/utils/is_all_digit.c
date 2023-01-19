/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:26 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:26 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_all_digit(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-' || content[i] == '+')
		i++;
	while (content[i] != '\0')
	{
		if (ft_isdigit(content[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}
