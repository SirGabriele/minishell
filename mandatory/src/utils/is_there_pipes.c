/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:54 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:54 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_pipes(t_token_ms	*tokens)
{
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
