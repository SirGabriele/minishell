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
