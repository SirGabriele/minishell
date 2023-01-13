/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:59:21 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/13 13:59:22 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	makeshift_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*arr;
	size_t	i;
	size_t	j;
	size_t	lens1s2;

	i = 0;
	j = 0;
	lens1s2 = makeshift_strlen(s1) + makeshift_strlen(s2);
	arr = malloc(sizeof(char) * (lens1s2 + 1));
	if (arr == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2 && j < n && s2[j] != '\0')
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}
