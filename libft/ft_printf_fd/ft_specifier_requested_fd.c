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

static char	*ft_putcharprintf_fd(unsigned char c)
{
	char	*to_add;

	to_add = malloc(sizeof(char) * 2);
	to_add[0] = c;
	to_add[1] = '\0';
	return (to_add);
}

static char	*ft_print_memory_fd(unsigned long long int arg)
{
	char	*to_add;

	if (!arg)
	{
		to_add = ft_strdup("(nil)");
		return (to_add);
	}
	else
	{
		to_add = ft_strdup("0x");
		to_add = ft_strjoin_free_both(to_add, ft_putnbrbaseprintf_fd(arg,
					"0123456789abcdef"));
	}
	return (to_add);
}

char	*replace_percentage(char specifier, va_list param)
{
	char	*to_add;

	if (specifier == 'c')
		to_add = ft_putcharprintf_fd((unsigned char)va_arg(param, int));
	else if (specifier == 's')
		to_add = ft_putstrprintf_fd(va_arg(param, char *));
	else if (specifier == 'p')
		to_add = ft_print_memory_fd(va_arg(param, unsigned long long int));
	else if (specifier == 'd' || specifier == 'i')
		to_add = ft_itoa(va_arg(param, int));
	else if (specifier == 'u')
		to_add = ft_putnbrbaseprintf_fd(va_arg(param, unsigned int),
				"0123456789");
	else if (specifier == 'x')
		to_add = ft_putnbrbaseprintf_fd(va_arg(param, unsigned int),
				"0123456789abcdef");
	else if (specifier == 'X')
		to_add = ft_putnbrbaseprintf_fd(va_arg(param, unsigned int),
				"0123456789ABCDEF");
	else
		to_add = ft_strdup("%");
	return (to_add);
}
