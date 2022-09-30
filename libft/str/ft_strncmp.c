/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:38:25 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/04 13:53:21 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s3[i] != '\0' && i <= n)
	{
		if (s3[i] > s4[i] || s3[i] < s4[i])
			return (s3[i] - s4[i]);
		else if (s3[i] == s4[i])
		{
			i++;
			if (i == n)
				return (0);
		}
	}
	if (s4[i] != '\0')
		return (-s4[i]);
	return (0);
}
