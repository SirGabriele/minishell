/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_asked_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:51:35 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/20 20:15:30 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbrbaseprintf_error(unsigned int nbr, char *base, int *i)
{
	if ((size_t)nbr >= ft_strlen(base))
	{
		ft_putnbrbaseprintf_error(nbr / ft_strlen(base), base, i);
		ft_putnbrbaseprintf_error(nbr % ft_strlen(base), base, i);
	}
	else if ((size_t)nbr < ft_strlen(base))
		ft_putcharprintf_error(base[nbr], i);
}

static void	ft_putmemory_error(unsigned long long int nbr, char *base, int *i)
{
	if (nbr >= ft_strlen(base))
	{
		ft_putmemory_error(nbr / ft_strlen(base), base, i);
		ft_putmemory_error(nbr % ft_strlen(base), base, i);
	}
	else if (nbr < ft_strlen(base))
		ft_putcharprintf_error(base[nbr], i);
}

static void	ft_print_memory_error(unsigned long long int arg, int *i)
{
	unsigned long long int	*argp;

	argp = &arg;
	if (!arg)
	{
		write(2, "(nil)", 5);
		*i = *i + 5;
		return ;
	}
	else if (arg > 0)
	{
		ft_putstrprintf_error("0x", i);
		ft_putmemory_error(*argp, "0123456789abcdef", i);
	}
	return ;
}

static void	ft_putnbrprintf_error(long long int nbr, int *i)
{
	if (nbr < 0)
	{
		write(2, "-", 1);
		(*i)++;
		ft_putnbrprintf_error(-nbr, i);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ft_putcharprintf_error(nbr % 10 + 48, i);
	}
	else if (nbr >= 10)
	{
		ft_putnbrprintf_error(nbr / 10, i);
		ft_putnbrprintf_error(nbr % 10, i);
	}
}

void	ft_specifier_asked_error(const char **fmt, int *i, va_list param)
{
	if (**fmt == 'c')
		ft_putcharprintf_error((unsigned char)va_arg(param, int), i);
	else if (**fmt == 's')
		ft_putstrprintf_error(va_arg(param, char *), i);
	else if (**fmt == 'p')
		ft_print_memory_error(va_arg(param, unsigned long long int), i);
	else if (**fmt == 'd')
		ft_putnbrprintf_error(va_arg(param, int), i);
	else if (**fmt == 'i')
		ft_putnbrprintf_error(va_arg(param, int), i);
	else if (**fmt == 'u')
		ft_putnbrprintf_error(va_arg(param, unsigned int), i);
	else if (**fmt == 'x')
		ft_putnbrbaseprintf_error(va_arg(param, unsigned int),
			"0123456789abcdef", i);
	else if (**fmt == 'X')
		ft_putnbrbaseprintf_error(va_arg(param, unsigned int),
			"0123456789ABCDEF", i);
	else if (**fmt == '%')
		ft_putcharprintf_error('%', i);
}
