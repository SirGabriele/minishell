/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:15:26 by kbrousse          #+#    #+#             */
/*   Updated: 2022/06/23 15:13:11 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*retcheck;

	if (!lst || !f || !del)
		return (NULL);
	retcheck = ft_lstnew(f(lst->content));
	ret = retcheck;
	while (lst->next != NULL)
	{
		lst = lst->next;
		retcheck->next = ft_lstnew(f(lst->content));
		if (retcheck == NULL)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		retcheck = retcheck->next;
	}
	return (ret);
}
