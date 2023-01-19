/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_type_a_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:06 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:07 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_token_type_a_redir(t_enum_token token_type)
{
	if (token_type == TOK_INFILE)
		return (1);
	if (token_type == TOK_TRUNC)
		return (2);
	if (token_type == TOK_HEREDOC)
		return (3);
	if (token_type == TOK_APPEND)
		return (4);
	return (0);
}
