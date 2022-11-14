/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:30:53 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/23 04:33:22 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_lstaddback_pipex(t_pipex *pipex, t_pipex_cmd *new)
{
	t_pipex_cmd	*copy;

	copy = pipex->first_cmd;
	while (copy->next != NULL)
		copy = copy->next;
	copy->next = new;
}
