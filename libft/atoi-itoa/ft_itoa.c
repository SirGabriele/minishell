/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:03:13 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/08 13:34:09 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	len_int(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*fill_malloc(char *tab, int len_int, int n)
{
	tab[len_int] = '\0';
	if (n >= 0)
	{
		while (len_int > 0)
		{
			tab[len_int - 1] = (n % 10) + 48;
			n = n / 10;
			len_int--;
		}
	}
	else if (n < 0)
	{
		tab[0] = '-';
		n = -n;
		while (len_int > 1)
		{
			tab[len_int - 1] = (n % 10) + 48;
			n = n / 10;
			len_int--;
		}
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;

	if (n == -2147483648)
	{
		tab = malloc(sizeof(char) * 11 + 1);
		if (tab == NULL)
			return (NULL);
		n = -214748364;
		tab = fill_malloc(tab, len_int(n), n);
		tab[10] = '8';
		tab[11] = '\0';
		return (tab);
	}
	if (n > 2147483647 || n < -2147483647)
		return (0);
	tab = malloc(sizeof(char) * len_int(n) + 1);
	if (tab == NULL)
		return (NULL);
	tab = fill_malloc(tab, len_int(n), n);
	return (tab);
}
