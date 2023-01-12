/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:40:20 by kbrousse          #+#    #+#             */
/*   Updated: 2022/10/04 10:58:41 by jsauvain         ###   ########.fr       */
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

char	*ft_strnjoin_free_first(char *s1, char const *s2, size_t n)
{
	char	*tab;
	size_t	i;
	size_t	j;
	size_t	lens1s2;

	i = 0;
	j = 0;
	lens1s2 = makeshift_strlen(s1) + n;
	tab = malloc(sizeof(char) * (lens1s2 + 1));
	if (tab == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2 && j < n && s2[j] != '\0')
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	if (s1 != NULL)
		free(s1);
	return (tab);
}
