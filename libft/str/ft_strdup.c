/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:08:18 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/06 14:21:45 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	makeshift_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*makeshift_strcat(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = malloc(sizeof(char) * makeshift_strlen(s) + 1);
	if (dup == NULL)
		return (NULL);
	makeshift_strcat(dup, s);
	return (dup);
}
