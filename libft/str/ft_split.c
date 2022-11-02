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

#include "../libft.h"

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

static char	*fill_string(char *arr, const char *s, int n, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	while (i < n)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static char	**fill_arr(char const *s, char c, int nb_cells, char **arr)
{
	int		i;
	int		j;
	int		substrlen;

	i = 0;
	j = 0;
	while (j < nb_cells)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		substrlen = ft_substrlen(s + i, c);
		arr[j] = malloc(sizeof(char) * substrlen + 1);
		if (arr[j] == NULL)
		{
			free_arr(arr);
			return (NULL);
		}
		fill_string(arr[j], s + i, substrlen, c);
		while (s[i] != c && s[i] != '\0')
			i++;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		nb_cells;

	if (!s)
		return (NULL);
	nb_cells = howmanysep(s, c);
	arr = malloc(sizeof(char *) * (nb_cells + 1));
	if (arr == NULL)
		return (NULL);
	fill_arr(s, c, nb_cells, arr);
	return (arr);
}
