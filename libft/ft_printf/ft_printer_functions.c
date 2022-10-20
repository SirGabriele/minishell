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

void	ft_putnbrbaseprintf(unsigned int nbr, char *base, int *i)
{
	if ((size_t)nbr >= ft_strlen(base))
	{
		ft_putnbrbaseprintf(nbr / ft_strlen(base), base, i);
		ft_putnbrbaseprintf(nbr % ft_strlen(base), base, i);
	}
	else if ((size_t)nbr < ft_strlen(base))
		ft_putcharprintf(base[nbr], i);
}

void	ft_print_memory(unsigned long long int arg, int *i)
{
	unsigned long long int	*argp;

	argp = &arg;
	if (!arg)
	{
		write(1, "(nil)", 5);
		*i = *i + 5;
		return ;
	}
	else if (arg > 0)
	{
		ft_putstrprintf("0x", i);
		ft_putmemory(*argp, "0123456789abcdef", i);
	}
	return ;
}
