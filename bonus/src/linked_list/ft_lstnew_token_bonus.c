/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_token_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:13:46 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:13:47 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_token_ms	*ft_lstnew_token(void)
{
	t_token_ms	*elem;

	elem = malloc(sizeof(t_token_ms));
	if (!elem)
	{
		perror(NULL);
		return (NULL);
	}
	elem->type = 0;
	elem->content = NULL;
	elem->next = NULL;
	return (elem);
}
