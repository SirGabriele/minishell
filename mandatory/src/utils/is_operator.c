/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:47 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:48 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(t_enum_token type)
{
	if (type == TOK_AND_OPER || type == TOK_OR_OPER || type == TOK_PIPE)
		return (1);
	return (0);
}
