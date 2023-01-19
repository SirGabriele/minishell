/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_dollar_conditions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:06 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:46:54 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	examine_dollar_conditions(char *content, int i)
{
	if (ft_isspace(content[i + 1]))
		return (1);
	if (content[i + 1] == '$')
		return (1);
	if (content[i + 1] == '\0')
		return (1);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
		&& is_it_a_closed_quote(content + i + 2, content[i + 1]))
		return (1);
	if (ft_isdigit(content[i + 1]))
		return (2);
	if ((content[i + 1] == '\"' || content[i + 1] == '\'')
		&& !is_it_a_closed_quote(content + i + 2, content[i + 1])
		&& !is_dollar_inside_quotes(content, i))
		return (3);
	return (0);
}
