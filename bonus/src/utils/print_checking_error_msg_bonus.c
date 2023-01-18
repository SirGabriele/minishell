/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_checking_error_msg_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:02 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:07:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	print_checking_error_msg(char *msg)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", msg);
}
