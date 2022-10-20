/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:49:53 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/20 20:13:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_ERROR_H
# define FT_PRINTF_ERROR_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf_error(const char *format, ...);
void	ft_specifier_asked_error(const char **fmt, int *i, va_list param);
void	ft_flag_asked_error(const char **fmt, int *i, va_list param);
void	ft_putcharprintf_error(unsigned const char c, int *i);
void	ft_putstrprintf_error(char *str, int *i);
void	ft_putnbrbaseprintf_error(unsigned int nbr, char *base, int *i);
void	ft_putnbrprintf_error(long long int nbr, int *i);
void	ft_print_memory_error(unsigned long long int arg, int *i);
size_t	ft_strlen(const char *str);
void	ft_putmemory_error(unsigned long long int nbr, char *base, int *i);
int		ft_is_a_specifier_error(const char c);

#endif
