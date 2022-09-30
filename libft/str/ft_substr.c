/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:57:56 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/07 15:34:58 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	makeshift_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*subarray;

	i = 0;
	j = -1;
	if (s == NULL)
		return (NULL);
	if (start >= makeshift_strlen(s))
	{
		subarray = malloc(1);
		subarray[0] = '\0';
		return (subarray);
	}
	if (len > makeshift_strlen(s + start))
		len = makeshift_strlen(s + start);
	subarray = malloc(sizeof(char) * len + 1);
	if (subarray == NULL)
		return (NULL);
	while (i != start && i <= makeshift_strlen(s))
		i++;
	while (++j < len)
		subarray[j] = s[i + j];
	subarray[j] = '\0';
	return (subarray);
}
