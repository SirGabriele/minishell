/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_requested.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:51:35 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/01 23:33:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_specifier_requested_fd(const char **fmt, int *i, \
			va_list param, int fd)
{
	if (**fmt == 'c')
		ft_putcharprintf_fd((unsigned char)va_arg(param, int), i, fd);
	else if (**fmt == 's')
		ft_putstrprintf_fd(va_arg(param, char *), i, fd);
	else if (**fmt == 'p')
		ft_print_memory_fd(va_arg(param, unsigned long long int), i, fd);
	else if (**fmt == 'd')
		ft_putnbrprintf_fd(va_arg(param, int), i, fd);
	else if (**fmt == 'i')
		ft_putnbrprintf_fd(va_arg(param, int), i, fd);
	else if (**fmt == 'u')
		ft_putnbrprintf_fd(va_arg(param, unsigned int), i, fd);
	else if (**fmt == 'x')
		ft_putnbrbaseprintf_fd(va_arg(param, unsigned int), \
			"0123456789abcdef", i, fd);
	else if (**fmt == 'X')
		ft_putnbrbaseprintf_fd(va_arg(param, unsigned int), \
			"0123456789ABCDEF", i, fd);
	else if (**fmt == '%')
		ft_putcharprintf_fd('%', i, fd);
}

void	ft_putnbrprintf_fd(long long int nbr, int *i, int fd)
{
	if (nbr < 0)
	{
		write(fd, "-", 1);
		(*i)++;
		ft_putnbrprintf_fd(-nbr, i, fd);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ft_putcharprintf_fd(nbr % 10 + 48, i, fd);
	}
	else if (nbr >= 10)
	{
		ft_putnbrprintf_fd(nbr / 10, i, fd);
		ft_putnbrprintf_fd(nbr % 10, i, fd);
	}
}

void	ft_putmemory_fd(unsigned long long int nbr, char *base, int *i, int fd)
{
	if (nbr >= ft_strlen(base))
	{
		ft_putmemory_fd(nbr / ft_strlen(base), base, i, fd);
		ft_putmemory_fd(nbr % ft_strlen(base), base, i, fd);
	}
	else if (nbr < ft_strlen(base))
		ft_putcharprintf_fd(base[nbr], i, fd);
}
