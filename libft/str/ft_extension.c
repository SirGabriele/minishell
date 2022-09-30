/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argomez <argomez@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:30:24 by argomez           #+#    #+#             */
/*   Updated: 2022/05/24 13:44:03 by argomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_extension(const char *str, const char *ext)
{
	int	str_len;
	int	ext_len;

	str_len = ft_strlen(str);
	ext_len = ft_strlen(ext);
	if (str_len <= ext_len)
		return (10);
	while (str_len-- > 0 && ext_len-- > 0)
	{
		if (str[str_len] != ext[ext_len])
			return (10);
	}
	return (0);
}
