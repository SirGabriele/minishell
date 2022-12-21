/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:25:57 by jsauvain          #+#    #+#             */
/*   Updated: 2022/12/19 15:41:01 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*malloc_right_size(const char *s, int n)
{
	char	*dup;

	if (n > get_strlen(s))
	{
		dup = malloc((get_strlen(s) + 1) * sizeof(char));
		dup[get_strlen(s)] = '\0';
	}
	else
	{
		dup = malloc((n + 1) * sizeof(char));
		dup[n] = '\0';
	}
	return (dup);
}

static char	*makeshift_strcat(char *dst, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;

	dup = malloc_right_size(s, n);
	if (dup == NULL)
		return (NULL);
	makeshift_strcat(dup, s, n);
	return (dup);
}
