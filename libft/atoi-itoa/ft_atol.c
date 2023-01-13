/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:30 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/13 15:46:24 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long int	ft_atol(const char *nbr)
{
	long int	number;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	number = 0;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == 43 || nbr[i] == 45)
	{
		if (nbr[i] == 45)
			sign = -sign;
		i++;
	}
	while (nbr[i] >= 48 && nbr[i] <= 57)
	{
		number = number * 10 + (nbr[i] - 48);
		i++;
	}
	return (sign * number);
}
