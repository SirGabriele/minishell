/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_dollar_conditions_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:10:33 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:10:34 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
