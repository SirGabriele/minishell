/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:33:24 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/01 23:26:39 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_is_a_specifier_fd(const char c)
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

static char	*fill_final_string(const char *fmt, va_list param)
{
	static char	*final_string = NULL;
	char		*to_add;
	static int	i = 0;
	int			j;

	to_add = NULL;
	if (fmt[i] && fmt[i] == '%' && ft_is_a_specifier_fd(fmt[i + 1]) == 1)
	{
		to_add = replace_percentage(fmt[i + 1], param);
		final_string = ft_strjoin_free_both(final_string, to_add);
		i += 2;
		fill_final_string(fmt, param);
	}
	j = 0;
	while (fmt[i] && fmt[i + j]
		&& !(fmt[i + j] == '%' && ft_is_a_specifier_fd(fmt[i + j]) == 1))
		j++;
	{
		final_string = ft_strnjoin_free_first(final_string, fmt + i, j);
		i = i + j;
	}
	if (fmt[i])
		fill_final_string(fmt, param);
	return (final_string);
}

int	ft_printf_fd(int fd, const char *fmt, ...)
{
	char	*final_string;
	int		len;
	va_list	param;

	len = 1;
	if (!fmt)
		return (1);
	va_start(param, fmt);
	final_string = fill_final_string(fmt, param);
	if (final_string == NULL)
	{
		ft_printf_fd(2, "Error occured while filling ft_printf_fd's buffer\n");
		return (1);
	}
	else
	{
		len = ft_strlen(final_string);
		write(fd, final_string, len);
		free(final_string);
	}		
	va_end(param);
	return (len);
}
