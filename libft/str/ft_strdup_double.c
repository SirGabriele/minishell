/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:10:58 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/21 07:47:42 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_len_src(const char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		i++;
	return (i);
}

char	**ft_strdup_double(const char **src)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (get_len_src(src) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
	{
		arr[i] = ft_strdup (src[i]);
		if (arr[i] == NULL)
		{
			free_double_arr(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
