/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_pipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:33:30 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/23 04:36:02 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

t_pipex_cmd	*ft_lstnew_pipex(t_pipex *pipex)
{
	t_pipex_cmd	*elem;

	elem = ft_calloc(1, sizeof(t_pipex_cmd));
	if (elem == NULL)
		clear_program(pipex, "In ft_lstnew_pipex.c, malloc failed");
	elem->correct_path = NULL;
	elem->tab_cmd = NULL;
	return (elem);
}
