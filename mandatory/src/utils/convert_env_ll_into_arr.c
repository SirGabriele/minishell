/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_ll_into_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:42:50 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:42:51 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_len_linked_list(t_env_ms *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*associate_key_value(t_env_ms *env)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, env->key);
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, "=");
	if (str == NULL)
		return (NULL);
	str = ft_strjoin_free_first(str, env->value);
	if (str == NULL)
		return (NULL);
	return (str);
}

/****************************************************************/
/*																*/
/*	Converts the linked list containing all the environment		*/
/*		variables into a double array							*/
/*																*/
/*	Parameters:													*/
/*		env	-	the linked list containing all env variables	*/
/*																*/
/*	Return:														*/
/*		arr		-	the double array							*/
/*		NULL	-	malloc failed								*/
/*																*/
/****************************************************************/

char	**convert_env_ll_into_arr(t_env_ms *env)
{
	char	**arr;
	int		len_linked_list;
	int		i;

	len_linked_list = get_len_linked_list(env);
	arr = malloc(sizeof(char *) * (len_linked_list + 1));
	if (arr == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	i = 0;
	while (env != NULL)
	{
		arr[i] = associate_key_value(env);
		if (arr[i] == NULL)
		{
			free_double_arr(arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
