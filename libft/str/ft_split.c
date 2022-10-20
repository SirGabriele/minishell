/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:20:47 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/07 17:18:29 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	howmanysep(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	count++;
	return (count);
}

static int	len_substring(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	*fill_string(char *tab, const char *s, int n, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	while (i < n)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (howmanysep(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (++j < howmanysep(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		tab[j] = malloc(sizeof(char) * len_substring(s + i, c) + 1);
		if (tab[j] == NULL)
			return (NULL);
		fill_string(tab[j], s + i, len_substring(s + i, c), c);
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
