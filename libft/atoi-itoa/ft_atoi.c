/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:06:39 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/04 15:25:01 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nbr)
{
	int	i;
	int	sign;
	int	number;

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
