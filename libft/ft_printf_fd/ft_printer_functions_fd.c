/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:53:40 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/01 23:33:32 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_putstrprintf_fd(char *str)
{
	char	*to_add;

	if (!str)
	{
		to_add = ft_strdup("(null)");
		return (to_add);
	}
	else
		to_add = ft_strdup(str);
	return (to_add);
}

char	*ft_putnbrbaseprintf_fd(unsigned int nbr, char *base)
{
	static char			number[500];
	char				*to_add;
	static int			i = 0;
	static unsigned int	true_nbr = 0;

	to_add = NULL;
	if (true_nbr == 0)
		true_nbr = nbr;
	if ((size_t)nbr >= ft_strlen(base))
	{
		ft_putnbrbaseprintf_fd(nbr / ft_strlen(base), base);
		ft_putnbrbaseprintf_fd(nbr % ft_strlen(base), base);
	}
	else if ((size_t)nbr < ft_strlen(base))
		number[i++] = base[nbr];
	if (nbr == true_nbr)
	{
		to_add = ft_strdup(number);
		true_nbr = 0;
		ft_bzero(number, 500);
		i = 0;
	}
	return (to_add);
}
