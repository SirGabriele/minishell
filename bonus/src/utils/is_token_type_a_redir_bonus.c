/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_type_a_redir_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:10:21 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:10:21 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
