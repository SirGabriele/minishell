/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:43:32 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/03 09:47:00 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **str, char *options)
{
	int	i;

	i = 0;
	while (str[i + 1])
		ft_printf("%s", str[i++]);
	if (ft_strncmp(options, "-n", ft_strlen(options)))
		ft_printf("\n");
	return (0);
}
