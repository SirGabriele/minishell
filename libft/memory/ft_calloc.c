/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:29:37 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/07 18:17:36 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t size, size_t nmemb)
{
	unsigned char	*arr;
	size_t			i;

	i = 0;
	if (size > 2147483647 || nmemb > 2147483647)
		return (NULL);
	arr = malloc(size * nmemb);
	if (arr == NULL)
		return (NULL);
	else if (nmemb * size > 2147483647)
		return (NULL);
	while (i < nmemb * size)
	{
		arr[i] = '\0';
		i++;
	}
	return ((void *)arr);
}
