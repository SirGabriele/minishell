/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:49:03 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/07 19:34:15 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	const char	*copy_dst;

	i = ft_strlen(dst);
	j = 0;
	copy_dst = (const char *)dst;
	if (size == 0)
		return (ft_strlen(src));
	else if (size <= ft_strlen(copy_dst))
		return (ft_strlen(src) + size);
	while (i < size - 1 && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ft_strlen(copy_dst) + ft_strlen(src) - j);
}
