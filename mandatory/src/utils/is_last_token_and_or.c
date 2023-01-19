/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_last_token_and_or.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:42 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:43 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_last_token_and_or(t_token_ms *tokens)
{
	while (tokens != NULL)
	{
		if ((tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER)
			&& !tokens->next)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
