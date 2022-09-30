/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 09:54:02 by kbrousse          #+#    #+#             */
/*   Updated: 2022/03/05 23:51:34 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] <= 90 && str[index] >= 65)
		{
			str[index] = str[index] + 32;
		}
		index++;
	}
	return (str);
}

char	*ft_strcapitalize(char *str)
{
	int	index;

	index = 0;
	ft_strlowcase(str);
	while (str[index] != '\0')
	{
		if (str[0] >= 97 && str[0] <= 122)
			str[0] = str[0] - 32;
		else if (str[index] <= 47 || (str[index] >= 58 && str[index] <= 64)
			|| (str[index] >= 91 && str[index] <= 96)
			|| (str[index] >= 123 && str[index] <= 126))
		{
			if (str[index + 1] >= 97 && str[index + 1] <= 122)
				str[index + 1] = str[index + 1] - 32;
		}
		index++;
	}
	return (str);
}
