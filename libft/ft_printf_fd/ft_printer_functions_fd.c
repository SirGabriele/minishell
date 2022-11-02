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

void	ft_putcharprintf_fd(unsigned const char c, int *i, int fd)
{
	write(fd, &c, 1);
	*i = *i + 1;
}

void	ft_putstrprintf_fd(char *str, int *i, int fd)
{
	if (!str)
	{
		write(fd, "(null)", 6);
		*i = *i + 6;
		return ;
	}
	while (*str != '\0')
	{
		ft_putcharprintf_fd(*str, i, fd);
		str++;
	}
}

void	ft_putnbrbaseprintf_fd(unsigned int nbr, char *base, int *i, int fd)
{
	if ((size_t)nbr >= ft_strlen(base))
	{
		ft_putnbrbaseprintf_fd(nbr / ft_strlen(base), base, i, fd);
		ft_putnbrbaseprintf_fd(nbr % ft_strlen(base), base, i, fd);
	}
	else if ((size_t)nbr < ft_strlen(base))
		ft_putcharprintf_fd(base[nbr], i, fd);
}

void	ft_print_memory_fd(unsigned long long int arg, int *i, int fd)
{
	unsigned long long int	*argp;

	argp = &arg;
	if (!arg)
	{
		write(fd, "(nil)", 5);
		*i = *i + 5;
		return ;
	}
	else if (arg > 0)
	{
		ft_putstrprintf_fd("0x", i, fd);
		ft_putmemory_fd(*argp, "0123456789abcdef", i, fd);
	}
	return ;
}
