/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer_functions_error.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:53:40 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/18 16:25:10 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putcharprintf_error(unsigned const char c, int *i)
{
	write(2, &c, 1);
	*i = *i + 1;
}

void	ft_putstrprintf_error(char *str, int *i)
{
	if (!str)
	{
		write(2, "(null)", 6);
		*i = *i + 6;
		return ;
	}
	while (*str != '\0')
	{
		ft_putcharprintf_error(*str, i);
		str++;
	}
}

void	ft_putnbrbaseprintf_error(unsigned int nbr, char *base, int *i)
{
	if ((size_t)nbr >= ft_strlen(base))
	{
		ft_putnbrbaseprintf_error(nbr / ft_strlen(base), base, i);
		ft_putnbrbaseprintf_error(nbr % ft_strlen(base), base, i);
	}
	else if ((size_t)nbr < ft_strlen(base))
		ft_putcharprintf_error(base[nbr], i);
}

void	ft_print_memory_error(unsigned long long int arg, int *i)
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
