/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 19:13:20 by kbrousse          #+#    #+#             */
/*   Updated: 2022/04/12 14:54:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lstcpy;

	if (!lst)
		return ;
	lstcpy = *lst;
	while (lstcpy != NULL)
	{
		lstcpy = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = lstcpy;
	}
	*lst = NULL;
}
