/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_requested.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:51:35 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/18 16:57:22 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_specifier_requested(const char **fmt, int *i, va_list param)
{
	if (**fmt == 'c')
		ft_putcharprintf((unsigned char)va_arg(param, int), i);
	else if (**fmt == 's')
		ft_putstrprintf(va_arg(param, char *), i);
	else if (**fmt == 'p')
		ft_print_memory(va_arg(param, unsigned long long int), i);
	else if (**fmt == 'd')
		ft_putnbrprintf(va_arg(param, int), i);
	else if (**fmt == 'i')
		ft_putnbrprintf(va_arg(param, int), i);
	else if (**fmt == 'u')
		ft_putnbrprintf(va_arg(param, unsigned int), i);
	else if (**fmt == 'x')
		ft_putnbrbaseprintf(va_arg(param, unsigned int), "0123456789abcdef", i);
	else if (**fmt == 'X')
		ft_putnbrbaseprintf(va_arg(param, unsigned int), "0123456789ABCDEF", i);
	else if (**fmt == '%')
		ft_putcharprintf('%', i);
}

void	ft_putnbrprintf(long long int nbr, int *i)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		(*i)++;
		ft_putnbrprintf(-nbr, i);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ft_putcharprintf(nbr % 10 + 48, i);
	}
	else if (nbr >= 10)
	{
		ft_putnbrprintf(nbr / 10, i);
		ft_putnbrprintf(nbr % 10, i);
	}
}

void	ft_putmemory(unsigned long long int nbr, char *base, int *i)
{
	if (nbr >= ft_strlen(base))
	{
		ft_putmemory(nbr / ft_strlen(base), base, i);
		ft_putmemory(nbr % ft_strlen(base), base, i);
	}
	else if (nbr < ft_strlen(base))
		ft_putcharprintf(base[nbr], i);
}
