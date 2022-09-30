/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:48:14 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/06 14:13:44 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_casted;

	i = 0;
	s_casted = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	if ((unsigned char)c == 0)
	{
		while (s_casted[i] != '\0')
			i++;
		return ((void *)s_casted + i);
	}
	while (i < n)
	{
		if (s_casted[i] == (unsigned char)c)
			return ((void *)s_casted + i);
		i++;
	}
	return (NULL);
}
