/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:53:40 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/18 16:25:10 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putcharprintf(unsigned const char c, int *i)
{
	write(1, &c, 1);
	*i = *i + 1;
}

void	ft_putstrprintf(char *str, int *i)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*i = *i + 6;
		return ;
	}
	while (*str != '\0')
	{
		ft_putcharprintf(*str, i);
		str++;
	}
}
