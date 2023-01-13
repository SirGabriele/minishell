/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_free_both.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:59:44 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/13 13:59:44 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	free_both(char *s1, char *s2)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
}

static int	makeshift_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnjoin_free_both(char *s1, char *s2, size_t n)
{
	char	*tab;
	size_t	i;
	size_t	j;
	size_t	lens1s2;

	i = 0;
	j = 0;
	lens1s2 = makeshift_strlen(s1) + makeshift_strlen(s2);
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
	free_both(s1, s2);
	return (tab);
}
