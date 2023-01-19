/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight_syntax_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:37:41 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 23:10:05 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_after_end(const char *str, int end, int line)
{
	int	i;

	i = 0;
	while (i <= end)
		i++;
	while (str[i] != '\0')
	{
		if (line == 0)
			ft_printf("%c", str[i]);
		else if (line == 1)
		{
			if (ft_isprint(str[i]) == 1)
				ft_printf(" ", str[i]);
			else
				ft_printf("%c", str[i]);
		}
		i++;
	}
}

static void	print_syntax_error(const char *str, int start, int end, int line)
{
	int	i;

	i = 0;
	while (i < start)
		i++;
	while (i <= end)
	{
		if (line == 0)
			ft_printf("\e[1;91m%c\e[0m", str[i]);
		else if (line == 1)
			ft_printf("\e[1;91m^\e[0m");
		i++;
	}
}

static void	print_before_start(const char *str, int start, int line)
{
	int	i;

	i = 0;
	while (i < start)
	{
		if (line == 0)
			ft_printf("%c", str[i]);
		else if (line == 1)
		{
			if (ft_isprint(str[i]) == 1)
				ft_printf(" ");
			else
				ft_printf("%c", str[i]);
		}
		i++;
	}
}

void	highlight_syntax_error(const char *str, int start, int end)
{
	int	line;

	line = 0;
	while (line < 2)
	{
		print_before_start(str, start, line);
		print_syntax_error(str, start, end, line);
		print_after_end(str, end, line);
		ft_putchar('\n');
		line++;
	}
}
