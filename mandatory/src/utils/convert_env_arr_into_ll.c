/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_arr_into_ll.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:42:42 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:42:45 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Converts the double array containing all the environment	*/
/*		variables into linked list								*/
/*																*/
/*	Parameters:													*/
/*		env	-	the doubl earray containing all env variables	*/
/*																*/
/*	Return:														*/
/*		first_link	-	the first link of the list				*/
/*		NULL		-	malloc failed							*/
/*																*/
/****************************************************************/

t_env_ms	*convert_env_arr_into_ll(const char **env)
{
	t_env_ms	*first_link;
	t_env_ms	*cursor;
	int			i;

	i = 0;
	first_link = ft_lstnew_env_entry(env[i]);
	if (first_link == NULL)
		return (NULL);
	cursor = first_link;
	i++;
	while (env[i] != NULL)
	{
		cursor->next = ft_lstnew_env_entry(env[i]);
		cursor = cursor->next;
		i++;
	}
	cursor->next = ft_lstnew_env_entry("?=0");
	return (first_link);
}
