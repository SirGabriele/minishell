/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:34:54 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/08 15:32:57 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	isinset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static char	*makeshift_memcpy(char *tab, const char *s1, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		tab[i] = s1[i];
		i++;
	}
	return (tab);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	if (!s1)
		return (NULL);
	while (isinset(s1[i], set) == 1)
		i++;
	if (s1[i] == '\0')
	{
		tab = malloc(1);
		tab[0] = '\0';
		return (tab);
	}
	j = ft_strlen(&s1[i]) - 1;
	while (isinset(s1[i + j], set) == 1)
		j--;
	j++;
	tab = malloc(sizeof(char) * (j + 1));
	if (tab == NULL)
		return (NULL);
	makeshift_memcpy(tab, s1 + i, j);
	tab[j] = '\0';
	return (tab);
}
