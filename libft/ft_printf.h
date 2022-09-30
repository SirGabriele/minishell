/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:49:53 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/20 20:13:21 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_specifier_requested(const char **fmt, int *i, va_list param);
void	ft_flag_requested(const char **fmt, int *i, va_list param);
void	ft_putcharprintf(unsigned const char c, int *i);
void	ft_putstrprintf(char *str, int *i);
void	ft_putnbrbaseprintf(unsigned int nbr, char *base, int *i);
void	ft_putnbrprintf(long long int nbr, int *i);
void	ft_print_memory(unsigned long long int arg, int *i);
size_t	ft_strlen(const char *str);
void	ft_putmemory(unsigned long long int nbr, char *base, int *i);
int		ft_is_a_specifier(const char c);

#endif
