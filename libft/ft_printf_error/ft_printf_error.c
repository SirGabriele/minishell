/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:33:24 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/20 20:15:49 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_is_a_specifier_error(const char c)
{
	char	s[10];
	int		i;

	s[0] = 'c';
	s[1] = 's';
	s[2] = 'p';
	s[3] = 'd';
	s[4] = 'i';
	s[5] = 'u';
	s[6] = 'x';
	s[7] = 'X';
	s[8] = '%';
	s[9] = '\0';
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	ft_scan_after_percent_error(const char *fmt, int *i, va_list param)
{
	int	booly;

	booly = 0;
	if (ft_is_a_specifier_error(*fmt) == 1)
	{
		booly++;
		ft_specifier_asked_error(&fmt, i, param);
	}
	return (booly);
}

int	ft_printf_error(const char *fmt, ...)
{
	int			i;
	va_list		param;

	i = 0;
	va_start(param, fmt);
	if (!fmt)
		return (0);
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (ft_scan_after_percent_error(fmt, &i, param) == 0)
				return (0);
			fmt++;
		}
		else
		{
			write(2, fmt, 1);
			fmt++;
			i++;
		}
	}
	va_end(param);
	return (i);
}
