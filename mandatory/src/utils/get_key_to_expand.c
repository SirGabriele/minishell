/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_to_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:13 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/21 04:55:36 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key_to_expand(char *content)
{
	char	*key_to_expand;
	int		j;

	j = 0;
	while (content[j] != ' ' && content[j] != '\"'
		&& content[j] != '$' && content[j] != '\0'
		&& content[j] != '\'' && content[j] != '='
		&& content[j] != '?')
		j++;
	if (!j && (content[j] == '?' || content[j] == '0'))
		j++;
	if (ft_isdigit(content[0]) && content[0] != '0')
		key_to_expand = ft_strndup(content + 1, j);
	else
		key_to_expand = ft_strndup(content, j);
	if (key_to_expand == NULL)
	{
		free(content);
		perror(NULL);
		return (NULL);
	}
	return (key_to_expand);
}
