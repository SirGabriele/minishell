/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digit_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:50 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:07:50 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
